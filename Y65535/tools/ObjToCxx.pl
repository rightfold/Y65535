#!/usr/bin/env perl

use strict;
use warnings;

my @positions;
my @normals;
my @faces;

while (<STDIN>) {
    printf("// %s", $_);

    chomp;
    next if /^#/;

    my @fields = split;

    if ($fields[0] eq 'v') {
        my @position = @fields[1..3];
        push(@positions, \@position);
    }

    if ($fields[0] eq 'vn') {
        my @normal = @fields[1..3];
        push(@normals, \@normal);
    }

    if ($fields[0] eq 'f') {
        my @face = map {
            my @components = split(/\//);
            { position => ($components[0] or 0) - 1
            , texture  => ($components[1] or 0) - 1
            , normal   => ($components[2] or 0) - 1 }
        } @fields[1..3];
        push(@faces, \@face);
    }
}

for my $face (@faces) {
    for my $vertex (@$face) {
        my $position = $positions[$vertex->{position}];
        my $normal   = $normals  [$vertex->{normal}];
        printf("{\n");
        printf("glm::vec3(%sf, %sf, %sf),\n", @$position);
        printf("glm::vec3(%sf, %sf, %sf),\n", @$normal);
        printf("},\n");
    }
}
