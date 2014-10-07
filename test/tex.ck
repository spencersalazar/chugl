// test OpenGL/chugl texture

512 => float WIDTH;
512 => float HEIGHT;

chugl gfx;
gfx.gl @=> OpenGL @ gl;

gfx.openWindow(WIDTH, HEIGHT);

[-50.0, -50.0,
  50.0, -50.0,
 -50.0,  50.0,
  50.0,  50.0 ]
@=> float geo[];

[0.0, 0.0, 
 1.0, 0.0, 
 0.0, 1.0,
 1.0, 1.0]
@=> float texcoord[];

while(!gfx.good())
    10::ms => now;

chuglImage img;
img.load(me.dir()+"hand.jpg");

while(true)
{
    gfx.lock();
    gfx.beginDraw();
    gfx.clear();
    
    //gl.Color4fv([1.0, 0.0, 0.0, 1.0]);
    gl.Color4fv([1.0, 1.0, 1.0, 1.0]);
    
    gl.Translatef(WIDTH/2, HEIGHT/2, 0.0);
    gl.Rotatef(now/second*180, 0, 0, 1);
    
    gl.VertexPointer(2, gl.FLOAT, 0, geo);
    gl.EnableClientState(gl.VERTEX_ARRAY);
    
    gl.Enable(gl.TEXTURE_2D);
    gl.BindTexture(gl.TEXTURE_2D, img.tex());
    gl.TexCoordPointer(2, gl.FLOAT, 0, texcoord);
    gl.EnableClientState(gl.TEXTURE_COORD_ARRAY);
    
    gl.DisableClientState(gl.COLOR_ARRAY);
    
    gl.DrawArrays(gl.TRIANGLE_STRIP, 0, 4);
    
    gfx.endDraw();
    gfx.unlock();
    
    (1.0/60.0)::second => now;
}
