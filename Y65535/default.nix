{ stdenv, blender, glew, glfw, glm, perl, xxd }:
let
    blendAsset = path: stdenv.mkDerivation {
        name = builtins.replaceStrings ["/" "."] ["_" "_"] path;
        buildInputs = [blender perl];
        phases = ["buildPhase" "installPhase"];
        buildPhase = ''
            blender '${./. + ("/" + path)}' --background --python '${./tools/BlendToObj.py}'
            perl '${./tools/ObjToCxx.pl}' < 'scene.obj' > 'asset.ipp'
        '';
        installPhase = ''
            mkdir -p "$out/$(dirname '${path}')"
            mv 'asset.ipp' "$out"'/${path}.ipp'
        '';
    };

    stringAsset = path: stdenv.mkDerivation {
        name = builtins.replaceStrings ["/" "."] ["_" "_"] path;
        buildInputs = [xxd];
        phases = ["buildPhase" "installPhase"];
        buildPhase = ''
            { cat '${./. + ("/" + path)}'; printf '\0'; } | xxd -i > 'asset.ipp'
        '';
        installPhase = ''
            mkdir -p "$out/$(dirname '${path}')"
            mv 'asset.ipp' "$out"'/${path}.ipp'
        '';
    };
in
    stdenv.mkDerivation {
        name = "Y65535";
        src = ./.;
        buildInputs = [
            glew
            glfw
            glm
            xxd
        ];
        buildPhase = ''
            cp -Rs '${blendAsset  "/src/Game/Assets/Bomb.blend"}/src' .
            cp -Rs '${blendAsset  "/src/Game/Assets/BulletA.blend"}/src' .
            cp -Rs '${blendAsset  "/src/Game/Assets/EnemyA.blend"}/src' .
            cp -Rs '${blendAsset  "/src/Game/Assets/ExplosionA.blend"}/src' .
            cp -Rs '${blendAsset  "/src/Game/Assets/JunkA.blend"}/src' .
            cp -Rs '${stringAsset "/src/Game/Assets/GenericShader.frag"}/src' .
            cp -Rs '${stringAsset "/src/Game/Assets/GenericShader.vert"}/src' .
            cp -Rs '${stringAsset "/src/Game/Assets/ParticleShader.frag"}/src' .
            cp -Rs '${stringAsset "/src/Game/Assets/ParticleShader.vert"}/src' .

            make -f tools/Makefile -j4
        '';
        installPhase = ''
            mkdir -p "$out/bin"
            mv 'a.out' "$out/bin/Y65535"
        '';
    }
