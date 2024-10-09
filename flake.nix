{
  description = "DWM: Dynamic Window Manager";

  inputs.nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";

  outputs = { self, nixpkgs }:
  let
    pkgs = nixpkgs.legacyPackages.x86_64-linux;
  in
  {
    packages.x86_64-linux.dwm = pkgs.callPackage (
      { lib, stdenv, fetchurl, libX11, libXinerama, libXft }:
        stdenv.mkDerivation rec {
          pname = "dwm";
          version = "6.3";
        
          src = ./.;
        
          buildInputs = [ libX11 libXinerama libXft ];
        
          makeFlags = [ "CC=${stdenv.cc.targetPrefix}cc" ];

	  installFlags = [ "PREFIX=$(out)" ];
	}
      ) {};

    packages.x86_64-linux.default = self.packages.x86_64-linux.dwm;

    devShells.x86_64-linux.default = pkgs.mkShell {
      packages = with pkgs; [
        xorg.libX11
	xorg.libXinerama
	xorg.libXft
      ];
    };
  };
}
