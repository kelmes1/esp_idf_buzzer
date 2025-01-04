# Passive Buzzer 无源蜂鸣器

![img](https://components.espressif.com/components/cdsama/buzzer/badge.svg)

## Overview

This is a library for driving a passive buzzer using ESP-IDF.  It provides some simple functions to control the buzzer and generate different tones.
这个库基于ESP-IDF驱动无源蜂鸣器。它提供了一些简单的函数来控制蜂鸣器并生成不同的音调。

## Features

- Supports all ESP-IDF targets
- Easy-to-use API for generating tones
- Configurable frequency and duration for tones

## Installation

To add this component to your project, run:

```sh
idf.py add-dependency "cdsama/buzzer^1.0.0"
```

or download the archive.

## Usage

Here is a basic example of how to use the library:

```cpp
#include "Buzzer.h"

Buzzer buz;

void app_main(void) {
    ESP_ERROR_CHECK(buz.init(GPIO_NUM_2));
    buz.Beep({.frequency = 1000, .duration_ms = 1000, .volume = 0.01f});
    vTaskDelay(pdMS_TO_TICKS(1000));
    buz.Play({{800, 200, 0.01f}, {500, 200, 0.01f}}); 
}
```

## License

MIT License


