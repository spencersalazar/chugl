// test OpenGL vector-based functions

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

while(true)
{
    gfx.clear();
    
    //gl.Color4fv([1.0, 0.0, 0.0, 1.0]);
    //gl.DisableClientState(gl.COLOR_ARRAY);
    // same as:
    gl.Color4dv([1.0, 0.0, 0.0, 1.0]);
    gl.DisableClientState(gl.COLOR_ARRAY);
    
    gl.Translatef(WIDTH/2, HEIGHT/2, 0.0);
    gl.Rotatef(now/second*180, 0, 0, 1);
    
    gl.VertexPointer(2, gl.DOUBLE, 0, geo);
    gl.EnableClientState(gl.VERTEX_ARRAY);
    
    gl.DrawArrays(gl.TRIANGLE_STRIP, 0, 4);
    
    (1.0/60.0)::second => now;
}
