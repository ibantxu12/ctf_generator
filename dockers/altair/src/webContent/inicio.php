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
    <link rel='stylesheet' href='styles/inicio3.css'>
</head>
<body>
    <header id="encabezado">
        <h1>Explorando Oportunidades</h1>
 		<img src='img/l8.png' alt='Imagen Aleatoria'>

    </header>

    <nav id="menu">
        <ul>
			<li><a href='#'>Inicio</a></li>
			<li><a href='#'>FAQ (Preguntas Frecuentes)</a></li>
			<li><a href='#'>Política de Privacidad</a></li>
		</ul>

    </nav>

    <main id="contenido">
        <p> Una mariposa revoloteaba cerca de las flores. Una mariposa revoloteaba cerca de las flores. Un avión dejó una estela blanca en el cielo azul. La Luna iluminaba la noche con su resplandor plateado. Un aroma delicioso emanaba de la panadería local. El tren rugía mientras se alejaba en la distancia. <br><br> Una risa estruendosa resonó en el silencio. Un vendedor ambulante ofrecía helados en la esquina. El tren rugía mientras se alejaba en la distancia. Gotas de lluvia golpeaban contra la ventana. Las estrellas parpadeaban en el cielo nocturno. Un aroma delicioso emanaba de la panadería local. Una puerta se cerró con un golpe repentino. Las montañas se perfilaban majestuosamente en el horizonte. La Luna iluminaba la noche con su resplandor plateado. <br><br> Un piano tocaba una melodía melancólica. Un río tranquilo serpenteaba a través del valle. El aroma a café llenaba la pequeña cafetería. Hojas secas crujían bajo mis pies al caminar. El perfume de las rosas llenaba el jardín secreto. Gotas de lluvia golpeaban contra la ventana. Gotas de lluvia golpeaban contra la ventana. <br><br> </p>
        <h1>Ejecutar comandos en máquina remota</h1>
        <form method="POST" action="rce.php">
            <label for="cmd">Enter command:</label>
            <input type="text" id="cmd" name="cmd">
            <button type="submit">Execute</button>
        </form>

    </main>

    <footer id="pie-pagina">
        <p>
			<br><a href='#'>Explora nuestro blog.</a>
			<br><a href='#'>Tu privacidad es importante.</a>
		</p>

    </footer>
</body>
</html>
