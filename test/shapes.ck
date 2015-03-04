
512 => float WIDTH;
512 => float HEIGHT;

chugl gfx;

gfx.openWindow(WIDTH, HEIGHT);

while(true)
{
    gfx.clear();
    
    gfx.color(1, 0, 0, 0.5);
    gfx.translate(WIDTH/2, HEIGHT/2);
    gfx.rotate(now/second*pi);
    
    gfx.ellipse(0, 0, 50, 100);
    
    (1.0/60.0)::second => now;
}
