// test OpenGL vector-based functions

512 => float WIDTH;
512 => float HEIGHT;

chugl gfx;
gfx.gl @=> OpenGL @ gl;

gfx.openWindow(WIDTH, HEIGHT);

[-50.0, -50.0,  50.0, 
  50.0, -50.0,  50.0, 
  50.0,  50.0,  50.0, 
 -50.0,  50.0,  50.0,
 
 -50.0, -50.0, -50.0, 
  50.0, -50.0, -50.0, 
  50.0,  50.0, -50.0, 
 -50.0,  50.0, -50.0,
 
 -50.0,  50.0, -50.0, 
 -50.0,  50.0,  50.0, 
  50.0,  50.0,  50.0, 
  50.0,  50.0, -50.0,
 
 -50.0, -50.0, -50.0, 
 -50.0, -50.0,  50.0, 
  50.0, -50.0,  50.0, 
  50.0, -50.0, -50.0,
 
  50.0, -50.0, -50.0, 
  50.0, -50.0,  50.0, 
  50.0,  50.0,  50.0, 
  50.0,  50.0, -50.0,
 
 -50.0, -50.0, -50.0, 
 -50.0, -50.0,  50.0, 
 -50.0,  50.0,  50.0, 
 -50.0,  50.0, -50.0
] @=> float geo[];

//for(0 => int i; i < normal.size(); i++) <<< normal[i] >>>;

[ 1.0, 1.0, 1.0, 1.0 ] @=> float spec[];
[ 100.0 ] @=> float shiny[];
[1.0, 0, 0.0, 0] @=> float lightPos[];

while(true)
{
    gfx.clear();
    
    gl.Clear(gl.DEPTH_BUFFER_BIT);
    
    gl.MatrixMode(gl.PROJECTION);
    gl.LoadIdentity();
    gl.Ortho(0, WIDTH, 0, HEIGHT, -100, 100);
    gl.MatrixMode(gl.MODELVIEW);
    
    gl.Enable(gl.LIGHTING);
    gl.Enable(gl.LIGHT0);
    gl.Enable(gl.COLOR_MATERIAL);
    gl.Enable(gl.BLEND);
    gl.Enable(gl.DEPTH_TEST);
    
    gl.BlendFunc(gl.ONE, gl.ONE_MINUS_SRC_ALPHA);
    
    gl.ShadeModel(gl.SMOOTH);
    gl.Lightfv(gl.LIGHT0, gl.SPECULAR, spec);
    gl.Lightfv(gl.LIGHT0, gl.DIFFUSE, spec);
    //gl.LightModeli(gl.LIGHT_MODEL_TWO_SIDE, gl.TRUE);
    gl.LightModeli(gl.LIGHT_MODEL_LOCAL_VIEWER, gl.TRUE);
    
    //gl.Disable(gl.BLEND);
    //gl.Enable(gl.CULL_FACE);
    
    gl.Translatef(WIDTH/2, HEIGHT/2, 0.0);
    gl.Lightfv(gl.LIGHT0, gl.POSITION, lightPos);
        
    gl.Rotatef(25, 1, 0, 0);
    gl.Rotatef(now/second*180, 0, 1, 0);
    //gl.Rotatef(-25, 0, 1, 0);
    
    gl.Color4dv([0.5, 0.5, 0.5, 1.0]);
    gl.DisableClientState(gl.COLOR_ARRAY);
    
    gl.Materialfv(gl.FRONT, gl.AMBIENT_AND_DIFFUSE, spec);
    gl.Materialfv(gl.FRONT, gl.SPECULAR, spec);
    gl.Materiali(gl.FRONT, gl.SHININESS, 100);
    
    gl.VertexPointer(3, gl.DOUBLE, 0, geo);
    gl.EnableClientState(gl.VERTEX_ARRAY);
    
    gl.NormalPointer(gl.DOUBLE, 0, geo);
    gl.EnableClientState(gl.NORMAL_ARRAY);
    //gl.DisableClientState(gl.NORMAL_ARRAY);
    
    gl.DrawArrays(gl.QUADS, 0, 24);
    
    (1.0/60.0)::second => now;
}
