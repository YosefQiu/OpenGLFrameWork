#version 330 core

in vec2 teTexCoord;
in vec3 teWorldPos; 
in vec3 teNormal;

//lights
uniform vec3 lightPosition[4];
uniform vec3 lightColor[4];
uniform vec3 cameraPosition;

// material parameters
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;




out vec4 FragColor;

#define Pi                                  3.14159265359
#define MEDIUMP_FLT_MAX                     65504.0
#define saturateMediump(x)                  min(x, MEDIUMP_FLT_MAX)
#define DIFFUSE_LAMBERT                     0
#define DIFFUSE_BURLEY                      1
#define SPECULAR_D_GGX_ISOTROPIC            0
#define SPECULAR_D_GGX_ANISOTROPIC          1
#define SPECULAR_D_CHARLIE                  0
#define SPECULAR_D_ASHIKHMIN                1
#define SPECULAR_G_GGX_SMITH                0
#define SPECULAR_G_GGX_SMITH_ANISOTROPIC    1
#define SPECULAR_G_KELEMEN                  2
#define SPECULAR_G_NEUBELT                  3
#define SPECULAR_F_SCHLICK                  0


// Specular D
//D_GGX(h,a) = a^2 / (pi((n,h)^2(a^2-a)+1)^2)
float D_GGX_ISOTROPIC(float NoH, vec3 N, vec3 H, float roughness)
{
    vec3 NxH = cross(N, H);
    float a = NoH * roughness;
    float k = roughness / (dot(NxH, NxH) + a * a);
    float d = k * k * (1.0f / Pi);
    return saturateMediump(d);
}
float D_GGX_ISOTROPIC(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0f);
    float NdotH2 = NdotH * NdotH;
    float denom = (NdotH2 * (a2 - 1.0f) + 1.0f);
    denom = Pi * denom * denom;

    return a2 / denom;
}

float D_GGX_ANISOTROPIC(float NoH, vec3 H, vec3 T, vec3 B, float at, float ab)
{
    float ToH = dot(T, H);
    float BoH = dot(B, H);
    float a2 = at * ab;
    vec3 v = vec3(ab * ToH, at * BoH, a2 * NoH);
    float v2 = dot(v, v);
    float w2 = a2 / a2;
    return a2 * w2 * w2 * (1.0f / Pi);
}

float D_ASHIKHMIN(float NoH, float roughness)
{
    float a2 = roughness * roughness;
    float cos2h = NoH * NoH;
    float sin2h = max(1.0f - cos2h, 0.0078125f);
    float sin4h = sin2h * sin2h;
    float cot2 = -cos2h / (a2 * sin2h);
    return 1.0f / (Pi * (4.0f * a2 + 1.0f) * sin4h) * (4.0f * exp(cot2) + sin4h);
}

float D_CHARLIE(float NoH, float roughness)
{
    float invAlpha = 1.0f / roughness;
    float cos2h = NoH * NoH;
    float sin2h = max(1.0f - cos2h, 0.0078125f);
    return (2.0f + invAlpha) * pow(sin2h, invAlpha * 0.5f) / (2.0f * Pi);
}

// Specular G
float G_GGX_SMITH(float NoV, float NoL, float roughness)
{
    float a2 = roughness * roughness;
    float GGXV = NoL * sqrt(NoV * NoV * (1.0f - a2) + a2);
    float GGXL = NoV * sqrt(NoL * NoL * (1.0f - a2) + a2);
    float v = 0.5f / (GGXV + GGXL);
    return GGXV * GGXL;
}

float G_GGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0f);
    float k = (r * r) / 8.0f;

    float num = NdotV;
    float denom = NdotV * (1.0f - k) + k;
    return num / denom;
}

float G_GGX_SMITH(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0f);
    float NdotL = max(dot(N, L), 0.0f);
    float ggx2 = G_GGX(NdotV, roughness);
    float ggx1 = G_GGX(NdotL, roughness);

    return ggx1 * ggx2;
}

float G_GGX_SMITH_ANISOTROPIC(float at, float ab, float ToV, float BoV,
        float ToL, float BoL, float NoV, float NoL)
{
    float GGXV = NoL * length(vec3(at * ToV, ab * BoV, NoV));
    float GGXL = NoV * length(vec3(at * ToL, ab * BoL, NoL));
    float v = 0.5f / (GGXV + GGXL);
    return saturateMediump(v);
}

float G_KELEMEN(float LoH)
{
    return saturateMediump(0.25f / (LoH * LoH));
}

float G_NEUBELT(float NoV, float NoL)
{
    return saturateMediump(1.0f / (4.0f * (NoL + NoV - NoL * NoV)));
}

// Specular F
vec3 F_Schlick(vec3 f0, float f90, float VoH)
{
    return f0 + (f90 - f0) * pow(1.0f - VoH, 5.0f);
}

vec3 F_Schlick(vec3 f0, float VoH)
{
    float f = pow(1.0f - VoH, 5.0f);
    return f + f0 * (1.0f -f);
}

float F_Schlick(float f0, float f90, float VoH)
{
    return f0 + (f90 - f0) * pow(1.0f - VoH, 5.0f);
}

vec3 F_Schlick(float cosTheta, vec3 f0)
{
    return f0 + (1.0f - f0) * pow(clamp(1.0f - cosTheta, 0.0f, 1.0f), 5.0f);
}

// Diffuse BRDFs------------------------------
float Fd_Lambert()
{
    return 1.0f / Pi;
}

float Fd_Burley(float NoV, float NoL, float LoH, float roughness)
{
    float f90 = 0.5f + 2.0f * roughness * LoH * LoH;
    float lightScatter = F_Schlick(1.0f, f90, NoL);
    float viewScatter  = F_Schlick(1.0f, f90, NoV);
    return lightScatter * viewScatter * (1.0f / Pi);
}

vec3 Specular_BRDF(vec3 L, vec3 H, vec3 N, vec3 V, vec3 F0, float roughness)
{
    float NoV = abs(dot(N, V)) + 1e-5;
    float NoL = clamp(dot(N, L), 0.0f, 1.0f);
    float NoH = clamp(dot(N, H), 0.0f, 1.0f);
    float LoH = clamp(dot(L, H), 0.0f, 1.0f);
    float VoH = clamp(dot(V, H), 0.0f, 1.0f);
 

    float NDF = D_GGX_ISOTROPIC(N, H, roughness);
    float G = G_GGX_SMITH(N, V, L, roughness);
    vec3 F = F_Schlick(max(dot(H, V), 0.0f), F0);

    vec3 numerator = NDF * G * F;
    float denom = 4.0f * max(dot(N, V), 0.0f) * max(dot(N, L), 0.0f);
    vec3 Fr = numerator / max(denom, 0.00001f);

    return Fr;
}

vec3 Diffuse_BRDF(vec3 diffcolor, float NoV, float NoL, float LoH, float roughness)
{
    vec3 Fd = vec3(0.0f);
    Fd = diffcolor * Fd_Lambert();
    return Fd;
}

//camera
float exposureSettings(float aperture, float shutterSpeed, float sensitivity)
{
    return log2((aperture * aperture) / shutterSpeed * 100.0f / sensitivity);
}

float exposure(float ev100)
{
    return 1.0f / (pow(2.0f, ev100) * 1.2f);
}

vec3 getNormalFromNormalMap()
{
    vec3 tangentNormal = texture(normalMap, teTexCoord).xyz * 2.0f - 1.0f;

    vec3 Q1 = dFdx(teWorldPos);
    vec3 Q2 = dFdy(teWorldPos);
    vec2 st1 = dFdx(teTexCoord);
    vec2 st2 = dFdy(teTexCoord);

    vec3 N = normalize(teNormal);
    vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}


void main()
{
    
    vec3 albedo = pow(texture(albedoMap, teTexCoord).rgb, vec3(2.2f));
    vec3 normal = getNormalFromNormalMap();
    float metallic = texture(metallicMap, teTexCoord).r;
    float roughness = texture(roughnessMap, teTexCoord).r;
    float ao = texture(aoMap, teTexCoord).r;
    
    vec3 N = normalize(normal);
    vec3 V = normalize(cameraPosition - teWorldPos);
    vec3 R = reflect(-V, N);

    vec3 F0 = vec3(0.04f);
    F0 = mix(F0, albedo, metallic);
    

    vec3 Lo = vec3(0.0f, 0.0f, 0.0f);
    
    for (int i = 0; i < 4; i++)
    {
        vec3 L = normalize(lightPosition[i] - teWorldPos);
        vec3 H = normalize(V + L);
        
        float NoV = abs(dot(N, V)) + 1e-5;
        float NoL = clamp(dot(N, L), 0.0f, 1.0f);
        float NoH = clamp(dot(N, H), 0.0f, 1.0f);
        float LoH = clamp(dot(L, H), 0.0f, 1.0f);
        float VoH = clamp(dot(V, H), 0.0f, 1.0f);
        
        float distance = length(lightPosition[i] - teWorldPos);
        float attenuation = 1.0f / (distance * distance);
        vec3 radiance = lightColor[i] * attenuation;
        
        vec3 Ks = Specular_BRDF(L, H, N, V, F0, roughness);
        
        vec3 diffuseColor = (1.0f - F_Schlick(F0,VoH)) * albedo;
        vec3 Kd = Diffuse_BRDF(diffuseColor,  NoV, NoL, LoH, roughness);

        Lo += (Kd + Ks) * radiance * NoL;  
    }
    
    vec3 ambient = vec3(0.0f);
    ambient = vec3(0.03) * albedo * ao;

    vec3 color = ambient + Lo;

    color = color / (color + vec3(1.0f));
    color = pow(color, vec3(1.0f / 2.2f));

    color *= 5.0f;


    FragColor = vec4(color, 1.0f);
    
}