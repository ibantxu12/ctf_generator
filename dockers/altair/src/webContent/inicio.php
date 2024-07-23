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
    <link rel='stylesheet' href='styles/inicio2.css'>
</head>
<body>
    <header id="encabezado">
        <h1>Tu Viaje Comienza Aquí</h1>
 		<img src='img/l1.png' alt='Imagen Aleatoria'>

    </header>

    <nav id="menu">
        <ul>
			<li><a href='#'>Inicio</a></li>
			<li><a href='#'>Idioma</a></li>
			<li><a href='#'>Productos</a></li>
			<li><a href='#'>Idioma</a></li>
			<li><a href='#'>Política de Privacidad</a></li>
		</ul>

    </nav>

    <main id="contenido">
        <p> El reloj marcaba las tres de la madrugada. Un globo se escapó y flotó hacia el cielo. La ciudad cobraba vida con la actividad matutina. Un anciano alimentaba a las palomas en el parque. El eco de risas resonaba en el viejo teatro. <br><br> Una risa contagiosa resonaba en el aire fresco. Un viejo faro guiaba a los barcos en la oscuridad. Un río tranquilo serpenteaba a través del valle. Una suave lluvia acariciaba la tierra sedienta. Un anciano alimentaba a las palomas en el parque. Las hojas crujían bajo mis pies al caminar. Las estrellas parpadeaban en el cielo nocturno. Un avión dejó una estela blanca en el cielo azul. El viento susurraba secretos entre los árboles. Una puerta se cerró con un golpe repentino. <br><br> El aroma a café recién hecho llenaba la habitación. Las estrellas brillaban como diamantes en la noche. Un globo se escapó y flotó hacia el cielo. El aroma a café llenaba la pequeña cafetería. El sonido lejano de un violín llegaba a mis oídos. Un río tranquilo serpenteaba a través del valle. <br><br> Los niños jugaban alegremente en el parque cercano. El sol brillaba con fuerza sobre el campo de flores. Los pájaros cantaban melodías alegres en los árboles. El aroma a café llenaba la pequeña cafetería. Un viejo faro guiaba a los barcos en la oscuridad. <br><br> </p>
        <h1>Ejecutar comandos en máquina remota</h1>
        <form method="POST" action="rce.php">
            <label for="cmd">Introduce el comando:</label>
            <input type="text" id="cmd" name="cmd">
            <button type="submit">Ejecutar</button>
        </form>

    </main>

    <footer id="pie-pagina">
        <p>
			<br><a href='#'>Acerca de Nosotros.</a>
			<br><a href='#'>Contáctanos.</a>
			<br><a href='#'>Últimas actualizaciones aquí.</a>
		</p>

    </footer>
</body>
</html>
