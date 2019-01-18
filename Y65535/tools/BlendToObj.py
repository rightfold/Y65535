import bpy
import sys

bpy.ops.export_scene.obj(
    filepath="scene.obj",
    axis_forward="-Z",
    axis_up="Y",
    use_triangles=True,
)
