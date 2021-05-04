# libformants

## Usage

To use the library you'll need to include the `libformants.h` header and in one of your compilation units (usually a `.c` file) define the `FORMANTS_IMPLEMENTATION` macro before including it.

First you need to create a workspace object, that will be reused between analysis runs.

```c
formants_work_t *work = formants_make_work(length, order);
```

It takes two parameters:
- the expected length in samples of the input audio signal,
- the linear prediction order that will be used for formant analysis.

Note that the length and order *can* change from run to run, but it does incur a performance penalty as the workspace needs to be rebuilt. You do not need to re-create the object for that to happen though.

The actual analysis happens here:

```c
unsigned long formantCount;
formant_t *formants = formants_analyze(
                    work, input, length, order,
                    sampleRate, margin,
                    &formantCount);
```

The `margin` parameter is used to exclude formant estimates that are outside of the `[margin, sampleRate / 2 - margin]` interval.

The returned array is allocated on the heap and the caller is the one who is expected to `free` it.
