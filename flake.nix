{
  description = "open-pet-tracker";

  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    nixpkgs-esp-dev.url = "github:mirrexagon/nixpkgs-esp-dev";
    nixpkgs.follows = "nixpkgs-esp-dev/nixpkgs";
  };

  outputs = { self, nixpkgs, flake-utils, nixpkgs-esp-dev }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [ nixpkgs-esp-dev.overlays.default ];
          config.permittedInsecurePackages = [
            "python3.13-ecdsa-0.19.1"
          ];
        };
      in
      {
        packages.open-pet-tracker = pkgs.stdenv.mkDerivation {
          pname = "open-pet-tracker";
          version = "0-unstable-2026-11-16";
          nativeBuildInputs = [ pkgs.esp-idf-full ];
          shellHook = ''
            export IDF_PATH="${pkgs.esp-idf-full}";
          '';
        };
        packages.default = self.packages.${system}.cattracker;
      }
    );
}
