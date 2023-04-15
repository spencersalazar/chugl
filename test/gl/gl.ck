
512 => float WIDTH;
512 => float HEIGHT;

chugl gfx;
gfx.gl @=> OpenGL @ gl;

gfx.openWindow(WIDTH, HEIGHT);

while(true)
{
    gfx.clear();
    
    gl.Color3f(1, 0, 0);
    gl.Translatef(WIDTH/2, HEIGHT/2, 0);
    gl.Rotatef(now/second*360.0, 0, 0, 1);
    
    gl.Begin(gl.QUADS);
    gl.Vertex3f(-50, -50, 0);
    gl.Vertex3f(-50,  50, 0);
    gl.Vertex3f( 50,  50, 0);
    gl.Vertex3f( 50, -50, 0);
    gl.End();
    
    (1.0/60.0)::second => now;
}
