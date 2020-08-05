uniform mediump sampler2D src;
varying mediump vec2 coord;

const mediump float widthFactor = 3.0;

uniform mediump float iTime;
uniform mediump float opacity_value;

uniform mediump vec3 bg_color;
uniform mediump vec3 line_color;

const mediump vec3 iResolution = vec3(1.0, 1.0, 1.0);

mediump vec3 calcSine(mediump vec2 uv, mediump float speed,
              mediump float frequency, mediump float amplitude, mediump float shift, mediump float offset,
              mediump vec3 color, mediump float width, mediump float exponent, bool dir)
{
    mediump float angle = iTime * speed * frequency * -1.0 + (shift + uv.x) * 2.0;

    mediump float y = sin(angle) * amplitude + offset;
    mediump float clampY = clamp(0.0, y, y);
    mediump float diffY = y - uv.y;

    mediump float dsqr = distance(y, uv.y);
    mediump float scale = 1.0;

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

void main(void)
{
    lowp vec4 tex = texture2D(src, coord);

    mediump vec2 uv = coord.xy / iResolution.xy;
    mediump vec3 color = bg_color;

    color += calcSine(uv, 0.2, 0.20, 0.20, 0.0, 0.6, line_color, 0.10, 15.0, false);
    color += calcSine(uv, 0.4, 0.40, 0.15, 0.0, 0.6, line_color, 0.10, 17.0, false);
    color += calcSine(uv, 0.3, 0.60, 0.15, 0.0, 0.6, line_color, 0.05, 23.0, false);

    color += calcSine(uv, 0.1, 0.26, 0.07, 0.0, 0.4, line_color, 0.10, 17.0, true);
    color += calcSine(uv, 0.3, 0.36, 0.07, 0.0, 0.4, line_color, 0.10, 17.0, true);
    color += calcSine(uv, 0.5, 0.46, 0.07, 0.0, 0.4, line_color, 0.05, 23.0, true);
    color += calcSine(uv, 0.2, 0.58, 0.05, 0.0, 0.4, line_color, 0.20, 15.0, true);

    gl_FragColor = vec4(color, 1.0) * opacity_value;
}
