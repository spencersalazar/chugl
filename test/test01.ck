
1::samp => now;

512 => float WIDTH;
512 => float HEIGHT;

chugl gfx;

gfx.openWindow(WIDTH, HEIGHT);

while(true)
{
    gfx.lock();
    gfx.beginDraw();
    gfx.clear();
    
    gfx.color(1, 0, 0, 0.5);
    gfx.translate(WIDTH/2, HEIGHT/2);
    gfx.rotate(now/second*pi);
    gfx.rect(-50, -50, 100, 100);
    
    gfx.endDraw();
    gfx.unlock();
    
    (1.0/60.0)::second => now;
}
