### Naming convention for resource files

|     Filetype      | Fileextension |
| :---------------: | :-----------: |
|   Basic Texture   |    \*.png     |
|       _-"-_       |    \*.jpg     |
|   Texture Atlas   |   \*.atlas    |
|     AnimationHandler     |    \*.anim    |
|   Vertex Shader   |    \*.vert    |
|  Fragment Shader  |    \*.frag    |

---

### AnimationHandler File Example:

```json
{
  "fps": 2,
  "atlas": "animation.atlas",
  "animations": [
    {
      "name": "idle",
      "frames": [
        {
          "x": 0,
          "y": 0,
          "w": 32,
          "h": 32
        },
        {
          "x": 32,
          "y": 32,
          "w": 32,
          "h": 32
        }
      ]
    }
  ]
}
```

---
