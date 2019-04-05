#shader vertex
#version 430 core

layout(location = 0) in vec2 vertice;
out vec2 v_fragCoords;

void main() {
	v_fragCoords = vec2(vertice.x, vertice.y);
	gl_Position = vec4(vertice, 0.0f, 1.0f);
}

#shader fragment
#version 430 core

in vec2 v_fragCoords;
out vec4 fragColor;

uniform vec2 u_center_offset;
uniform float u_zoom;
uniform int u_multibrot_power;
uniform int u_max_iteration;
uniform float u_escape_radius;
uniform vec3 u_hsv_color;
uniform int u_color_transition;
uniform float u_transition_exponent;

vec3 hsv2rgb(vec3 c)
{
	vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
	return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec2 complex_exp_prod(vec2 a, vec2 b) {
	return vec2(a.x * b.x, a.y + b.y);
}

vec2 complex_prod(vec2 a, vec2 b) {
	return vec2(a.x * b.x - a.y * b.y,
			a.y * b.x + b.y * a.x);
}

vec3 calculate_mandelbrot(vec2 c) {
	vec2 f = vec2(0.0f, 0.0f);
	float i = 0;
	vec2 f2 = c;
	float len = length(f2);
	for (i = 0; i < u_max_iteration && len < u_escape_radius && f != f2; i += 1.0f) {
		f = f2;
		for (int j = 0; j < u_multibrot_power - 1; ++j) f2 = complex_prod(f, f2);
		f2 += c;
		len = length(f2);
	}
	if (i == u_max_iteration || f == f2) return vec3(0.0f);
	if (i < u_max_iteration)
		i = i + 1 - log(len / log(u_max_iteration)) / log(u_multibrot_power);
	vec3 hsv_color = u_hsv_color;
	hsv_color[u_color_transition] = pow(fract(i / u_max_iteration), u_transition_exponent);
	return hsv2rgb(hsv_color);
}

void main() {
	fragColor = vec4(calculate_mandelbrot(u_zoom * v_fragCoords + u_center_offset), 1.0f);
}