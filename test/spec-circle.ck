
adc => FFT fft => blackhole;
4096 => fft.size;
Windowing.hamming(fft.size()/2) => fft.window;

complex spec[fft.size()/2];

chugl gfx;

gfx.fullscreen();
gfx.width() => float WIDTH;
gfx.height() => float HEIGHT;

while(true)
{
    // take fft
    fft.upchuck();
    // get contents
    fft.spectrum(spec);

    gfx.lock();
    gfx.beginDraw();
    
    gfx.clear();
    
    gfx.color(0.9, 0.2, 0.1, 1.0);
    
    gfx.translate(WIDTH/2, HEIGHT/4);
    //gfx.rotate(pi/2);

    for(int i; i < spec.size(); i++)
    {
        float dbAmp;
        
        gfx.pushMatrix();
        gfx.rotate(-(i$float)/spec.size()*pi);
        
        20*Math.log10((spec[i]$polar).mag) => dbAmp;
        Math.max(0, 110+dbAmp) => dbAmp;
        gfx.line(0, 0, 0, dbAmp*HEIGHT/100);
        
        gfx.popMatrix();
        
        gfx.pushMatrix();
        gfx.rotate((i$float)/spec.size()*pi);
        
        20*Math.log10((spec[i]$polar).mag) => dbAmp;
        Math.max(0, 110+dbAmp) => dbAmp;
        gfx.line(0, 0, 0, dbAmp*HEIGHT/100);
        
        gfx.popMatrix();
    }
    
    gfx.endDraw();
    gfx.unlock();
    
    (1.0/60.0)::second => now;
}
