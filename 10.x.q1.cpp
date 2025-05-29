int main()
{
    int a { 5 }; // 1a - none
    int b { 'a' }; // 1b - numeric promotion
    int c { 5.4 }; // 1c - error narrowing conversion
    int d { true }; // 1d - numeric promotion
    int e { static_cast<int>(5.4) }; // 1e - numeric conversion (in static_cast)

    double f { 5.0f }; // 1f - numeric promotion
    double g { 5 }; // 1g - error narrowing conversion [Actually: numeric conversion!]

    // Extra credit section
    long h { 5 }; // 1h - numeric promotion [Actually: numeric conversion!]

    float i { f }; // 1i (uses previously defined variable f) - numeric conversion [Actually: error narrowing conversion!]
    float j { 5.0 }; // 1j - none [Actually: numeric conversion!]

}