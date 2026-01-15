# Performance Analysis and Improvements

This document outlines identified performance issues and implemented improvements in the LunokIoT Watch firmware.

## Implemented Performance Fixes

### 1. Sorting Algorithm Optimization (Medium Priority)
**Location:** `src/system/lunokIoT.cpp`

**Issue:** The `ReverseBubbleSort` function used Bubble Sort algorithm with O(n²) time complexity.

**Fix:** Replaced with C standard library `qsort()` which has O(n log n) average time complexity. The comparison function uses proper comparison logic to avoid integer overflow.

**Impact:** Faster sorting of app usage data in the "Most Used Apps" feature, especially as the dataset grows.

```cpp
// Before: O(n²) Bubble Sort
for (i = 0; i < n - 1; i++)
    for (j = 0; j < n - i - 1; j++)
        if (arr[j] < arr[j + 1])
            Swap(arr,j,j + 1);

// After: O(n log n) QuickSort via qsort with overflow-safe comparison
static int CompareIntDescending(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ib < ia) return -1;
    if (ib > ia) return 1;
    return 0;
}
qsort(arr, n, sizeof(int), CompareIntDescending);
```

### 2. Sprite Copy Optimization (High Priority)
**Location:** `src/UI/UI.cpp` - `ScaleSprite()` function

**Issue:** When copying sprites at 1:1 scale (divisor = 1.0), the function performed slow pixel-by-pixel copying through a nested loop of 57,600 iterations (240x240 display).

**Fix:** Added fast path for 1:1 copy using the TFT_eSPI library's `pushRotated()` method which is hardware-accelerated. Uses named constants for tolerance thresholds.

**Impact:** Significant speedup in double-buffer initialization for watchfaces and other UI elements.

```cpp
// Named constants for maintainability
static const float SCALE_UNITY_MIN = 0.99f;
static const float SCALE_UNITY_MAX = 1.01f;

// Fast path for 1:1 copy
if ( divisor >= SCALE_UNITY_MIN && divisor <= SCALE_UNITY_MAX ) {
    view->setPivot(view->width()/2, view->height()/2);
    canvas->setPivot(canvas->width()/2, canvas->height()/2);
    view->pushRotated(canvas, 0);
    return canvas;
}
```

---

## Identified Performance Issues (Not Yet Fixed)

### 3. Pixel-by-Pixel Screen Updates (High Priority)
**Location:** `src/app/Watchface2.cpp:774-786`

**Issue:** The watchface double-buffer diff rendering iterates through every pixel (240x240 = 57,600 iterations) comparing old and new values using `readPixel()` and updating with `drawPixel()`.

**Potential Fix:** Consider using dirty rectangle tracking or region-based updates to only refresh changed areas. Alternatively, use DMA-based sprite push for full-screen updates when change percentage exceeds threshold.

### 4. Slow ScaleSpriteMAX Function (Medium Priority)
**Location:** `src/UI/UI.cpp:422-447`

**Issue:** Uses pixel-by-pixel copy similar to the original ScaleSprite.

**Potential Fix:** Could benefit from similar optimization for common scale factors.

### 5. Multiple readPixel Operations in Effects (Low Priority)
**Locations:** Various UI controls and transitions

**Issue:** Effects like blur, fade, and masking use multiple `readPixel()` calls which are slow SPI operations.

**Potential Fix:** Consider reading entire sprite buffer at once and operating on the pixel array directly.

### 6. Blocking Delays (Low Priority)
**Various Locations**

**Issue:** `delay()` calls in various places block the CPU.

**Note:** Some delays are necessary for hardware timing. Others could potentially use FreeRTOS task delays or timers for non-blocking behavior.

---

## Performance Best Practices for this Codebase

1. **Prefer `pushRotated()` or `pushSprite()` over pixel-by-pixel operations** when possible
2. **Use `qsort()` instead of custom O(n²) sorting algorithms**
3. **Minimize `readPixel()` calls** - read entire buffers when possible
4. **Use dirty rectangle tracking** for partial screen updates
5. **Avoid `delay()` in tick/render loops** - use timers or task delays instead
6. **Use `snprintf()` instead of `sprintf()`** for buffer safety

---

## Measuring Performance

The ESP32 provides timer functions for profiling:
```cpp
int64_t start = esp_timer_get_time();
// code to measure
int64_t end = esp_timer_get_time();
lLog("Elapsed: %lld us\n", end - start);
```
