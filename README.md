# Raytracer

Le programme utlise des scènes au format YAML pour créer une image représentant la scène. Les scènes sont à placer dans le dossier `scenes` à la racine du projet.

## Scène

Le fichier détaillant la scène est constitué de plusieurs attributs:

- `name` -> le nom de la scène qui apparait dans le sélecteur de scènes et qui sera le nom de l'image générée.

- `light` / `lights` -> la/les lumière(s) utilisée(s) pour éclairer la scène.

- `camera` -> la caméra qui enregistre tout ce qu'elle voit dans la scène.

- `objects` -> les objets de la scène (plane, square, spheres, cubes, ...)

Chacun de ces attributs possède d'autres attributs mais certains leurs sont communs, tels que:

    - position -> qui possède 3 attributs (x, y et z) qui est donc la position de l'entité. Peut être definie sur les entités: light, camera, objet. Si elle n'est pas définie, la position de l'entité sera par défaut x:0.0, y:0.0, z:0.0.

    - rotation -> qui possède 3 attributs (x, y et z) qui est donc la rotation de l'entité en degrés. Peut être définie sur les entités: light, camera, objet. Si elle n'est pas definie, la position de l'entité sera par défaut x:0.0, y:0.0, z:0.0.

Sur l'entité light, il est possible d'ajouter certains attributs:

    - diffuse -> qui possède 3 attributs (r, g et b) qui est la couleur de la lumière diffuse. Peut être définie sur light et tous les attributs material. Si elle n'est pas définie, la lumière sera blanche -> r = g = b = 255.
    - speculaire -> qui possède 3 attributs (r, g et b) qui est la couleur de la lumière spéculaire. Peut être définie sur light et tous les attributs material. Si elle n'est pas définie, la lumière sera blanche -> r = g = b = 255

```yaml
light:
  position:
    x: 1.0
    y: -3.0
    z: -0.5
  diffuse:
    r: 204.0
    g: 204.0
    b: 204.0
  specular:
    r: 128.0
    g: 128.0
    b: 128.0
```

Sur l'entité camera, il est possible d'ajouter certains attributs:

    - shadow -> qui active ou non les ombres sur la scène (true ou false).
    - resolution -> qui prend 2 attributs (width et height) qui est la taille de l'image.
    - focal -> qui est la distance focale de la camera.
    - position
    - rotation

Exemple:
```yaml
camera:  
  shadow: true  
  resolution:  
    width: 480  
    height: 480  
  focal: 2.0  
  position:  
    x: 0.0  
    y: -1.0  
    z: 0.5  
  rotation:  
    x: 10.0  
    y: 0  
    z: 0  
```

Sur l'attribut objects, on peut ajouter plusieurs objets dont le nom de l'attribut est à notre choix, exemple:
```yaml
objects:  
    premiere_sphere:  
        ...  
    deuxieme_sphere:  
        ...  
    mon_plane: 
        ...  
```

Chacun de ces attributs sera considéré comme un objet, ces objets ont plusieurs attributs:

    - type -> une string définissant le type de l'objet ("sphere", "cube", "plane", "square", ...).
    - position
    - rotation
    - material -> qui prend l'attribut ambiant (qui est la couleur par défaut d'un objet en r, g et b), l'attribut diffuse, l'attribut specular et l'attibut shininess (qui représente la brillance)
    - scale -> qui modifie la taille de l'objet: peut être un réel ou un vecteur (x, y, z)

```yaml
objects:
  sphere1:
    type: "sphere"
    position:
      x: 0.0
      y: -0.6
      z: -0.8
    material:
      ambiant:
        r: 25
        g: 128
        b: 25
      diffuse:
        r: 64
        g: 64
        b: 64
      specular:
        r: 191
        g: 191
        b: 191
      shininess: 3.0
```

L'attribut materials vient sous deux forme: `material` et `materials`. `materials` permet de specifier deux matériaux à utiliser pour l'objet. Il faut specifier l'attribut `type` ("checkerboard" ou "stripes" pour damier ou lignes) et ajouter un "-" pour definir les deux matériaux.

```yaml
objects:
  square1:
    type: "plane"
    position:
      x: 0.0
      y: 0.0
      z: -1.0
    rotation:
      x: 90
      y: 0.0
      z: 0.0
    materials:
      - type: "checkerboard"
      - ambiant:
          r: 0
          g: 120
          b: 214
        diffuse:
          r: 64
          g: 64
          b: 64
        specular:
          r: 191
          g: 191
          b: 191
        shininess: 3.0
      - ambiant:
          r: 241
          g: 79
          b: 33
        diffuse:
          r: 64
          g: 64
          b: 64
        specular:
          r: 191
          g: 191
          b: 191
        shininess: 3.0
```

Des exemple de scènes sont disponibles dans le dossier `scenes`.

## Explication algo

**Illumination** : Phong

**Matrice** : élimination de Gauss-Jordan pour l'inversion

## Explication programme

Création de l'image dans la fonction `render()` de la classe `Scene`, utilise `getImpactColor()` de la classe `Camera`.

main : gestion de la GUI, et appel à la fonction `render()` pour une scène donnée.

Les classes mathématiques (`Point`, `Vector`, `Matrice`, `Ray`) sont dans le dossier `maths` (.cpp dans `src/maths`, .hpp dans `include/maths`) et les classes concernant la scène (`Entity`, `Object`, `Camera`, `Color`, `Material`, ...) sont dans le dossier scene (.cpp dans `src/scene`, .hpp dans `include/scene`).

## Répartition des tâches

Axel COCAT ([robot0](https://github.com/robot0)) -> Classes maths (`Ray`, `Point`, `Vector`, `Matrice`, ...), GUI, multithread.

Yohann JERRAIN ([Kryod](https://github.com/Kryod)) -> Classes scène (`Entity`, `Scene`, `Object`, `Square`, `Plane`, `Sphere`, `Camera`, `Light`, ...), ombres, parsing scène -> yaml, readme.

## Bibliothèques utilisées

- **[OpenCV](https://github.com/opencv/opencv)**: matrice de pixels, enregistrement au format PNG. _([licence BSD](https://github.com/opencv/opencv/blob/master/LICENSE))_

- **[ImGui](https://github.com/ocornut/imgui)**: interface graphique. _([licence MIT](https://github.com/ocornut/imgui/blob/master/LICENSE.txt))_

- **[SFML](https://github.com/SFML/SFML)**: gestion de la fenêtre et de ses événements. _([licence](https://github.com/SFML/SFML/blob/master/license.md))_

- **[ImGui + SFML](https://github.com/eliasdaler/imgui-sfml)**: bindings pour utiliser ImGui avec SFML. _([licence MIT](https://github.com/eliasdaler/imgui-sfml/blob/master/LICENSE))_

- **[tinyfiledialogs](https://sourceforge.net/projects/tinyfiledialogs/)**: dialogues natifs d'enregistrement ou de choix de fichiers, boîtes de messages. _([licence zlib](https://sourceforge.net/directory/license:zlib/))_
