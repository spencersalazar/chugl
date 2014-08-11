
adc => FFT fft => blackhole;
4096 => fft.size;
Windowing.hamming(fft.size()/2) => fft.window;

complex spec[fft.size()/2];

chugl gfx;
gfx.gl @=> OpenGL @ gl;

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
        
    gl.Translatef(WIDTH/2, HEIGHT/4, 0);
    //gfx.rotate(pi/2);

    for(int i; i < spec.size(); i++)
    {
        float dbAmp;
        
        gl.PushMatrix();
        gl.Rotatef(-(i$float)/spec.size()*360.0, 0, 0, 1);
        
        20*Math.log10((spec[i]$polar).mag) => dbAmp;
        Math.max(0, 110+dbAmp) => dbAmp;
        gl.Begin(gl.LINES);
        gl.Vertex3f(0, 0, 0); gl.Color3f(0.9, 0.4, 0.1);
        gl.Vertex3f(0, dbAmp*HEIGHT/100, 0); gl.Color3f(1.0, 0.1, 0.1);
        gl.End();
        
        gl.PopMatrix();
        
        gl.PushMatrix();
        gl.Rotatef((i$float)/spec.size()*360.0, 0, 0, 1);
        
        20*Math.log10((spec[i]$polar).mag) => dbAmp;
        Math.max(0, 110+dbAmp) => dbAmp;
        gl.Begin(gl.LINES);
        gl.Vertex3f(0, 0, 0); gl.Color3f(0.9, 0.4, 0.1);
        gl.Vertex3f(0, dbAmp*HEIGHT/100, 0); gl.Color3f(1.0, 0.1, 0.1);
        gl.End();
        
        gl.PopMatrix();
    }
    
    gfx.endDraw();
    gfx.unlock();
    
    (1.0/60.0)::second => now;
}
