// test OpenGL/chugl texture

512 => float WIDTH;
512 => float HEIGHT;

chugl gfx;

gfx.openWindow(WIDTH, HEIGHT);

100 => float IMGWIDTH;
100 => float IMGHEIGHT;
chuglImage img;
img.load(me.dir()+"hand.jpg");

while(true)
{
    gfx.clear();
    
    img.draw(WIDTH/2-IMGWIDTH/2, HEIGHT/2-IMGHEIGHT/2, IMGWIDTH, IMGHEIGHT);
    
    (1.0/60.0)::second => now;
}
