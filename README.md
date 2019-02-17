# Raytracer

Le programme utlise des scènes au format yaml pour créer une image représentant la scène. Les scènes sont à placer dans le dossier `scenes`.

## Scene

Le fichier detaillant la scène est constitué de plusieurs attributs:

- name -> le nom de la scène qui apparait dans le selecteur de scène et qui sera le nom de l'image generer.

- light -> la lumiere utilisée pour éclairer la scène.

- camera -> la camera qui enregistre tout ce qu'elle voit dans l'image.

- objects -> les objets de la scène (plane, square, spheres, cubes, ...)

Chaqu'un de ses attributs possede d'autre attribut mais certains sont communs tel que:
    
    - position -> qui possede 3 attributs (x, y et z) qui est donc la position de l'entité. Peut etre definit sur les entité: light, camera, objet. Si elle n'est pas definit, la position de l'entiter sera par defaut x:0.0, y:0.0, z:0.0 .

    - rotation -> qui possede 3 attributs (x, y et z) qui est donc la rotation de l'entité en degrés. Peut etre definit sur les entité: light, camera, objet. Si elle n'est pas definit, la position de l'entiter sera par defaut x:0.0, y:0.0, z:0.0 .

Sur l'entité light, il est possible d'ajouter certains attributs:
    
    - diffuse -> qui possede 3 attributs (r, g et b) qui est la couleurs de la lumiere diffuse. Peut etre definis sur light et tous les attributs material. Si elle n'est pas definit, la lumiere sera blanche -> r = g = b = 255.
    - speculaire -> qui possede 3 attributs (r, g et b) qui est la couleurs de la lumiere speculaire. Peut etre definis sur light et tous les attributs material. Si elle n'est pas definit, la lumiere sera blanche -> r = g = b = 255

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

    - shadow -> qui active ou non les ombres sur la scene (true ou false).
    - resolution -> qui prend 2 attribut (width et height) qui est la taille de l'image.
    - focal -> qui est la distance focal de la camera.
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

Sur l'attribut objects, on peut ajouter plusieurs objets dont le nom de l'attribut est a notre choix, example:
```yaml
objects:  
    premiere_sphere:  
        ...  
    deuxieme_sphere:  
        ...  
    mon_plane: 
        ...  
```

Chaqu'un de ses attribut sera considerer comme un objet, ces objets ont plusieurs attribut:

    - type -> une string definissant le type de d'objet ("sphere", "cube", "plane", "square", ...).
    - position
    - rotation
    - material -> qui prend l'attribut ambiant (qui est la couleurs par defaut d'un objet en r, g et b), l'attribut diffuse, l'attribut specular et l'attibut shininess (qui represente la brillance)
    - scale -> qui modifie la taille de l'objet

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

L'attribut materials vient sous deux forme: material et materials. materials permet de specifier deux materiaux a utiliser pour l'objet. Il faut specifier l'attribut type ("checkerboard" ou "stripes" pour damier ou lignes) et ajouter un "-" pour definir les deux materiaux.

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

Illumination : Phong
Matrice : elimination de Gauss Jordan pour l'inversion

## Explication programme

Creation de l'image dans la fonction render() de la classe Scene, utilise getImpactColor() de la classe Camera.
main : setup la GUI, et appel la fonction render pour une scene donner.
Les classes mathematique (Point, Vector, Matrice, Ray) sont dans le dossier maths (.cpp -> `src/maths`, .hpp -> `include/maths`) et les classes concernant la scène (Entity, Object, Camera, Color, Material, ...) sont dans le dossier scene (.cpp -> `src/scene`, .hpp -> `include/scene`).

## Repartition des taches

Axel COCAT (Roboto) -> Classes maths (Ray, Point, Vector, Matrice, ...), GUI, multithread.
Yohann  JERRAIN (Kryod) -> Classes scene (entite, scene, objets, square, plane, sphere, camera, light, ...), Ombres, parsing scene/yaml, Readme.