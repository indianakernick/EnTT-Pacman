//
//  shaders.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 11/2/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_shaders_hpp
#define engine_graphics_2d_shaders_hpp

namespace G2D {
  const char CORE_SHADER_VERSION[] = "#version 330 core\n";
  const char ES_SHADER_VERSION[] = "#version 300 es\nprecision mediump float;\n";
  
  const char VERT_SHADER[] = R"delimiter(
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 color;

out vec2 fragTexCoord;
out vec4 fragColor;

uniform mat3 viewProj;

void main() {
  gl_Position.xy = (viewProj * vec3(pos.xy, 1.0)).xy;
  gl_Position.zw = vec2(pos.z, 1.0);
  fragTexCoord = texCoord;
  fragColor = color;
}
)delimiter";

  const char FRAG_SHADER[] = R"delimiter(
in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D tex;

out vec4 outColor;

void main() {
  const vec4 gamma = vec4(vec3(1.0/2.2), 1.0);
  outColor = pow(fragColor * texture(tex, fragTexCoord), gamma);
  gl_FragDepth = (outColor.a == 0.0 ? 1.0 : gl_FragCoord.z);
}
)delimiter";
}

#endif
