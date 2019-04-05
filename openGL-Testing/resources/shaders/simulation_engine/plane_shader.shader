#shader vertex
#version 330

layout(location = 0) in vec3 position;
out vec3 v_worldPos;
uniform mat4 u_view;
uniform mat4 u_proj;

void main() {
	gl_Position = u_proj * u_view * vec4(position, 1.0f);
	v_worldPos = position;
}

#shader fragment
#version 330

uniform vec3 u_color;

in vec3 v_worldPos;
out vec4 fragColor;
uniform vec3 u_center_offset;
uniform float u_zoom;

vec2 complex_prod(vec2 a, vec2 b) {
	return vec2(a.x * b.x - a.y * b.y, a.y * b.x + b.y * a.x);
}

vec3 calculate_mandelbrot(vec2 c) {
	vec2 f1 = vec2(0.0f);
	vec2 f2 = c;
	const int multibrot_const = 2;
	const float epsilon = 0.001f;
	int i = 0;
	for (i = 0; i < 100; ++i) {
		if (length(f2) > 2) break;
		f1 = f2;
		for (int j = 0; j < multibrot_const - 1; ++j) f2 = complex_prod(f2, f1);
		f2 += c;
	}
	return vec3(0.0f, float(i) / 100.0f, 0.0f);
}

vec3 get_color() {
	return calculate_mandelbrot((v_worldPos / u_size * 5.0f * u_zoom + u_center_offset).xz);
}

void main() {
	fragColor = vec4(get_color(), 1.0f);
}