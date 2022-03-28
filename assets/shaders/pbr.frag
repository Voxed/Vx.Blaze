#version 440 core
out vec4 FragColor;

in vec3 fNorm;
in vec3 wNorm;
in vec3 fPos;

#define PI 3.1415926538f

uniform vec3 COLOR;
uniform float ROUGHNESS;
uniform float METALNESS;

uniform sampler2D ENVIRONMENT;

void main()
{
    vec3 wo = normalize(-fPos);
    vec3 i = vec3(50.0f, 0.0f, 20.0f);
    vec3 wi = normalize(i - fPos);
    vec3 wh = normalize(wi + wo);

	float theta = acos(max(-1.0f, min(1.0f, wNorm.y)));
	float phi = atan(wNorm.z, wNorm.x);
	if (phi < 0.0f) phi = phi + 2.0f * PI;
	// Use these to lookup the color in the environment map
	vec2 lookup = vec2(phi / (2.0 * PI), theta / PI);
	vec4 c = texture(ENVIRONMENT, lookup);




    vec3 diff = COLOR*(1.0f/PI)*abs(dot(fNorm, wi)) * 2.0f;

    if(dot(fNorm, wi) <= 0) {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
        return;
    }

    float shine = (1.0f-ROUGHNESS)/ROUGHNESS*10.0f;
    //float D = (shine+2.0f)/(2.0f*PI)*(pow(dot(fNorm, wh), shine));

    float D = pow(ROUGHNESS, 2.0f)/(
        PI*pow(pow(dot(fNorm, wh), 2.0f)*(pow(ROUGHNESS, 2.0f) - 1.0f) + 1.0f ,2.0f)
    );

    vec3 F0 = vec3(0.04);
    F0      = mix(F0, COLOR, METALNESS);

    vec3 F = F0 + (1.0f - F0) * pow(1.0f - (dot(wh, wo)), 5.0f);

    float NdotV = max(dot(fNorm, wo), 0.0);
    float NdotL = max(dot(fNorm, wi), 0.0);

    float k = pow(ROUGHNESS + 1.0f, 2.0f)/8.0f;

    float ggx1 = (NdotV/(NdotV*(1.0f - k) + k));
    float ggx2 = (NdotL/(NdotL*(1.0f - k) + k));

    float G = ggx1 * ggx2;

    vec3 brdf = (D*G*F) / (4.0f*dot(fNorm, wo)*dot(fNorm, wi));

    vec3 d = brdf * dot(fNorm, wi) + (1.0f - F)*diff;
    vec3 me = brdf * COLOR * dot(fNorm, wi);
    vec3 mi = METALNESS * me + (1 - METALNESS) * d;

    FragColor = vec4((1.0f-ROUGHNESS) * mi + ROUGHNESS * diff, 1.0f);
}
