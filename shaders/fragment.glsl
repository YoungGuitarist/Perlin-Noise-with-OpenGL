#version 330 core
out vec4 FragColor;
in vec2 uv;

uniform float u_time;
uniform vec2 u_resolution;

float fade(float t) {
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

float grad(int hash, float x, float y) {
    int h = hash & 7;
    vec2 g = vec2(0.0);
    if (h == 0) g = vec2(1,1);
    else if (h == 1) g = vec2(-1,1);
    else if (h == 2) g = vec2(1,-1);
    else if (h == 3) g = vec2(-1,-1);
    else if (h == 4) g = vec2(1,0);
    else if (h == 5) g = vec2(-1,0);
    else if (h == 6) g = vec2(0,1);
    else g = vec2(0,-1);
    return g.x * x + g.y * y;
}

float hash(vec2 p) {
    return fract(sin(dot(p ,vec2(127.1,311.7))) * 43758.5453);
}

float perlin(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);

    float a = grad(int(hash(i + vec2(0,0)) * 8.0), f.x, f.y);
    float b = grad(int(hash(i + vec2(1,0)) * 8.0), f.x - 1.0, f.y);
    float c = grad(int(hash(i + vec2(0,1)) * 8.0), f.x, f.y - 1.0);
    float d = grad(int(hash(i + vec2(1,1)) * 8.0), f.x - 1.0, f.y - 1.0);

    vec2 u = vec2(fade(f.x), fade(f.y));
    return mix(mix(a, b, u.x), mix(c, d, u.x), u.y);
}

vec3 colorRamp(float t) {
    if (t < 0.33)
        return mix(vec3(0.4, 0.0, 0.0), vec3(1.0, 0.4, 0.0), t / 0.33); // Красный → Оранжевый
    else if (t < 0.66)
        return mix(vec3(1.0, 0.4, 0.0), vec3(1.0, 1.0, 0.0), (t - 0.33) / 0.33); // Оранжевый → Жёлтый
    else
        return mix(vec3(1.0, 1.0, 0.0), vec3(1.0, 1.0, 1.0), (t - 0.66) / 0.34); // Жёлтый → Белый
}


void main() {
    vec2 coord = gl_FragCoord.xy / u_resolution.xy * 8.0;
    float n = perlin(coord + vec2(u_time * 0.2));
    float val = n * 0.5 + 0.5;
    FragColor = vec4(colorRamp(val), 1.0);
}

