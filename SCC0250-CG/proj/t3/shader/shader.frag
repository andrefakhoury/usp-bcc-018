uniform vec3 light_pos;
vec3 light_color = vec3(1.0, 1.0, 1.0);

uniform float ka;
uniform float kd;
uniform float ks;
uniform float ns;

uniform vec3 view_pos;

varying vec3 out_position;
varying vec2 out_texture;
varying vec3 out_normal;

uniform sampler2D samplerTexture;

void main() {
    vec3 ambient = ka * light_color;

    vec3 norm = normalize(out_normal);
    vec3 light_dir = normalize(light_pos - out_position);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = kd * diff * light_color;

    vec3 view_dir = normalize(view_pos - out_position);
    vec3 reflect_dir = normalize(reflect(-light_dir, norm));
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), ns);
    vec3 specular = ks * spec * light_color;

    // use distance to source to calculate light intensity
    float dist = distance(light_pos, out_position) / 10.0;
    diffuse = diffuse * (1.0 / (1.0 + dist));
    specular = specular * (1.0 / (1.0 + dist));

    vec4 texture = texture2D(samplerTexture, out_texture);
    gl_FragColor = vec4((ambient + diffuse + specular), 1.0) * texture;
}