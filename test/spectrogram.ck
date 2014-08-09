
1::samp => now;

adc => FFT fft => blackhole;
4096 => fft.size;
Windowing.hamming(fft.size()/2) => fft.window;

complex spec[fft.size()/2];

1280 => float WIDTH;
WIDTH/16*9 => float HEIGHT;

chugl gfx;

gfx.openWindow(WIDTH, HEIGHT);

while(true)
{
    // take fft
    fft.upchuck();
    // get contents
    fft.spectrum(spec);

    gfx.lock();
    gfx.beginDraw();
    
    gfx.clear();
    
    gfx.color(0.9, 0.45, 0.1, 1.0);
    
    for(int i; i < spec.size(); i++)
    {
        20*Math.log10((spec[i]$polar).mag) => float dbAmp;
        gfx.line(0, 0, 0, (110+dbAmp)*7);
        gfx.translate(WIDTH/spec.size(), 0);
    }
    
    gfx.endDraw();
    gfx.unlock();
    
    (1.0/30)::second => now;
}
