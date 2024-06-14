{
  description = "Mmg";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        packages.default = pkgs.stdenv.mkDerivation {
          name = "mmg";

          src = ./.;

          nativeBuildInputs = with pkgs; [
            cmake
            perl
          ];

          preConfigure = ''
            patchShebangs ./
          '';

          cmakeFlags = [
            "-DBUILD_SHARED_LIBS:BOOL=TRUE"
            "-DMMG_INSTALL_PRIVATE_HEADERS=ON"
          ];
        };
      }
    );
}
