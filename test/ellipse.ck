
chugl gfx;
gfx.openWindow(512, 512);
gfx.width() => float WIDTH;
gfx.height() => float HEIGHT;

75 => float size;
10 => float velocity;
Math.random2f(0, 2*pi) => float angle;
Math.random2f(0, WIDTH) => float x;
Math.random2f(0, HEIGHT) => float y;
Math.random2f(0, 1) => float h;
Math.random2f(0.5, 0.8) => float s;
Math.random2f(0.5, 0.9) => float v;

while(true)
{
    // update
    
    velocity*Math.cos(angle) +=> x;
    velocity*Math.sin(angle) +=> y;
    
    if(x < size/2 || x > WIDTH-size/2)
    {
        // flip along y-axis
        Math.cos(angle) => float vx;
        Math.sin(angle) => float vy;
        Math.atan2(vy, -vx) => angle;
    }
    if(y < size/2 || y > HEIGHT-size/2)
    {
        // flip along x-axis
        Math.cos(angle) => float vx;
        Math.sin(angle) => float vy;
        Math.atan2(-vy, vx) => angle;
    }
    
    // render    
    gfx.hsv(h, s, v);
    gfx.ellipse(x, y, size, size);
    
    (1.0/60.0)::second => now;
}
