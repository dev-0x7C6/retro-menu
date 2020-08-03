uniform sampler2D src;
varying highp vec2 coord;

const vec3 top = vec3(0.17, 0.17, 0.17);
const vec3 bottom = vec3(0.17, 0.17, 0.17);
const vec3 line_color = vec3(0.1, 0.1, 0.1);
const float widthFactor = 3.0;

uniform float iTime;
uniform float opacity_value;

//const float iTime = 0.3;
const vec3 iResolution = vec3(1.0, 1.0, 1.0);

vec3 calcSine(vec2 uv, float speed,
              float frequency, float amplitude, float shift, float offset,
              vec3 color, float width, float exponent, bool dir)
{
    float angle = iTime * speed * frequency * -1.0 + (shift + uv.x) * 2.0;

    float y = sin(angle) * amplitude + offset;
    float clampY = clamp(0.0, y, y);
    float diffY = y - uv.y;

    float dsqr = distance(y, uv.y);
    float scale = 1.0;

    if(dir && diffY > 0.0)
    {
        dsqr = dsqr * 4.0;
    }
    else if(!dir && diffY < 0.0)
    {
        dsqr = dsqr * 4.0;
    }

    scale = pow(smoothstep(width * widthFactor, 0.0, dsqr), exponent);

    return min(color * scale, color);
}

void mainImage(out vec4 fragColor, in vec2 fragCoord )
{


}

void main(void)
{
    lowp vec4 tex = texture2D(src, coord);

    vec2 uv = coord.xy / iResolution.xy;
    vec3 color = vec3(mix(bottom, top, uv.y));

    color += calcSine(uv, 0.2, 0.20, 0.20, 0.0, 0.6, line_color, 0.10, 15.0, false);
    color += calcSine(uv, 0.4, 0.40, 0.15, 0.0, 0.6, line_color, 0.10, 17.0, false);
    color += calcSine(uv, 0.3, 0.60, 0.15, 0.0, 0.6, line_color, 0.05, 23.0, false);

    color += calcSine(uv, 0.1, 0.26, 0.07, 0.0, 0.4, line_color, 0.10, 17.0, true);
    color += calcSine(uv, 0.3, 0.36, 0.07, 0.0, 0.4, line_color, 0.10, 17.0, true);
    color += calcSine(uv, 0.5, 0.46, 0.07, 0.0, 0.4, line_color, 0.05, 23.0, true);
    color += calcSine(uv, 0.2, 0.58, 0.05, 0.0, 0.4, line_color, 0.20, 15.0, true);

    gl_FragColor = vec4(color, 1.0) * opacity_value;
}
