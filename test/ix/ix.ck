
chugl gfx;
gfx.openWindow(512, 512);
gfx.hideCursor();

while(true)
{
    gfx.clear();
    
    if(gfx.pointer.state)
    {
        gfx.color(1, 0, 0);
        gfx.ellipse(gfx.pointer.x, gfx.pointer.y, 25, 25);
    }
    else
    {
        gfx.color(0.3, 0.2, 0.2);
        gfx.ellipse(gfx.pointer.x, gfx.pointer.y, 25, 25);
    }
    
    (1.0/60.0)::second => now;
}
