typedef struct
{
    int A;
    int B;
} TwoTone;

#define FREQ_L1 697
#define FREQ_L2 770
#define FREQ_L3 852
#define FREQ_L4 941
#define FREQ_H1 1209
#define FREQ_H2 1336
#define FREQ_H3 1477
#define FREQ_H4 1633

enum Tone : int
{
    Tone_1 = 0,
    Tone_2 = 1,
    Tone_3 = 2,
    Tone_4 = 3,
    Tone_5 = 4,
    Tone_6 = 5,
    Tone_7 = 6,
    Tone_8 = 7,
    Tone_9 = 8,
    Tone_0 = 9,
    Tone_A = 10,
    Tone_B = 11,
    Tone_C = 12,
    Tone_D = 13,
    Tone_STAR = 14,
    Tone_HASH = 15,
};

TwoTone TONES[16] = {
    {FREQ_L1, FREQ_H1}, // Tone::Tone_1
    {FREQ_L1, FREQ_H2}, // Tone::Tone_2
    {FREQ_L1, FREQ_H3}, // Tone::Tone_3
    {FREQ_L2, FREQ_H1}, // Tone::Tone_4
    {FREQ_L2, FREQ_H2}, // Tone::Tone_5
    {FREQ_L2, FREQ_H3}, // Tone::Tone_6
    {FREQ_L3, FREQ_H1}, // Tone::Tone_7
    {FREQ_L3, FREQ_H2}, // Tone::Tone_8
    {FREQ_L3, FREQ_H3}, // Tone::Tone_9
    {FREQ_H4, FREQ_H2}, // Tone::Tone_0
    {FREQ_L1, FREQ_H4}, // Tone::Tone_A
    {FREQ_L2, FREQ_H4}, // Tone::Tone_B
    {FREQ_L3, FREQ_H4}, // Tone::Tone_C
    {FREQ_L4, FREQ_H4}, // Tone::Tone_D
    {FREQ_H4, FREQ_H1}, // Tone::Tone_STAR
    {FREQ_H4, FREQ_H3}, // Tone::Tone_HASH
};
