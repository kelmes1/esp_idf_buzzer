// Copyright (c) 2025 chendi
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "Buzzer.h"
#include "freertos/FreeRTOS.h"

// helper literal function to mark a tone as low, mid or high
constexpr int operator""_l(unsigned long long int Tone)
{
    return Tone;
}
constexpr int operator""_m(unsigned long long int Tone)
{
    return Tone + 7;
}
constexpr int operator""_h(unsigned long long int Tone)
{
    return Tone + 14;
}

Buzzer buz; // declare it at global scope, or it will be destroyed after app_main() returns

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(buz.Init(GPIO_NUM_13));

    for (int i = 1; i < 800; i++)
    {
        buz.Beep({.frequency = 10 * i, .duration_ms = 10, .volume = 0.01f}); // frequency test
        vTaskDelay(pdMS_TO_TICKS(10)); // Beep() or Play() is not a blocking function, so we may need to wait
                                       // playing time in sequence playing task
    }

    buz.Play({{800, 200, 0.01f}, {500, 200, 0.01f}}); // simple interactive sound
    vTaskDelay(pdMS_TO_TICKS(1000));

    // now lets try to play a music

    std::vector<int> music_keys = {
        0,                                       // start index
        262,  294,  330,  349,  392,  440,  494, // low
        523,  587,  659,  698,  784,  880,  988, // mid
        1046, 1175, 1318, 1397, 1568, 1760, 1976 // high
    };

    std::vector<std::pair<int, int>> melody = {
        {3_m, 4}, {3_m, 2}, {5_m, 2}, {6_m, 2}, {1_h, 2}, {1_h, 2}, {6_m, 2}, {5_m, 4}, {5_m, 2},
        {6_m, 2}, {5_m, 8}, // 好一朵美丽的茉莉花
        {3_m, 4}, {3_m, 2}, {5_m, 2}, {6_m, 2}, {1_h, 2}, {1_h, 2}, {6_m, 2}, {5_m, 4}, {5_m, 2},
        {6_m, 2}, {5_m, 8},                                                             // 好一朵美丽的茉莉花
        {5_m, 4}, {5_m, 4}, {5_m, 4}, {3_m, 2}, {5_m, 2}, {6_m, 4}, {6_m, 4}, {5_m, 8}, // 芬芳美丽满枝丫
        {3_m, 4}, {2_m, 2}, {3_m, 2}, {5_m, 4}, {3_m, 2}, {2_m, 2}, {1_m, 4}, {1_m, 2}, {2_m, 2},
        {1_m, 8}, // 又香又白人人夸
        {3_m, 2}, {2_m, 2}, {1_m, 2}, {3_m, 2}, {2_m, 6}, {3_m, 2}, {5_m, 4}, {6_m, 2}, {1_h, 2},
        {5_m, 8},                                                                       // 让我来将你摘下
        {2_m, 4}, {3_m, 2}, {5_m, 2}, {2_m, 2}, {3_m, 2}, {1_m, 2}, {6_l, 2}, {5_l, 8}, // 送给别人家
        {6_l, 4}, {1_m, 4}, {2_m, 6}, {3_m, 2}, {1_m, 2}, {2_m, 2}, {1_m, 2}, {6_l, 2}, {5_l, 10}, // 茉莉花 茉莉花
    };

    BuzzerMusic music;
    for (auto &note : melody)
    {
        music.push_back({music_keys[note.first], 150 * note.second, 0.01f});
        music.push_back({0, 10, 0.f});
    }

    buz.Play(music);
    uint32_t length = 0;
    for (auto &note : music)
    {
        length += note.duration_ms;
    }
    vTaskDelay(pdMS_TO_TICKS(length / 10)); // play for 1/10 of the total time, then stop
    buz.Stop();
    buz.Play(music); // play again, will stop after totally finished
}
