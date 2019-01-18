{ pkgs ? import ./nix/pkgs.nix {} }:
{
    Y65535 = pkgs.callPackage ./Y65535 {};
}
