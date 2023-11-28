<?php
session_start();

if (!isset($_SESSION['usuario'])) {
    header('Location: index.html');
    exit();
}

$usuario = $_SESSION['usuario'];
echo "<br>¡Bienvenid@, $usuario!<br><br>";

?>
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Inicio</title>
    <link rel='stylesheet' href='styles/inicio##estilo##.css'>
</head>
<body>
    <header id="encabezado">
        <!--encabezado-->
    </header>

    <nav id="menu">
        <!--menu-->
    </nav>

    <main id="contenido">
        <!--contenido-->
    </main>

    <footer id="pie-pagina">
        <!--pie-->
    </footer>
</body>
</html>
