varying vec2 out_texture;
uniform sampler2D samplerTexture;

void main(){
    gl_FragColor = texture2D(samplerTexture, out_texture);
}