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
    <link rel='stylesheet' href='styles/inicio1.css'>
</head>
<body>
    <header id="encabezado">
        <h1>Descubre Nuevas Experiencias</h1>
 		<img src='img/l6.png' alt='Imagen Aleatoria'>

    </header>

    <nav id="menu">
        <ul>
			<li><a href='#'>Inicio</a></li>
			<li><a href='#'>Blog</a></li>
			<li><a href='#'>Idioma</a></li>
		</ul>

    </nav>

    <main id="contenido">
        <p> La Luna iluminaba la noche con su resplandor plateado. Un aroma delicioso emanaba de la panadería local. Un aroma delicioso emanaba de la panadería local. Una suave lluvia acariciaba la tierra sedienta. Una sombra se movía en la penumbra de la calle. Un viejo faro guiaba a los barcos en la oscuridad. La Luna iluminaba la noche con su resplandor plateado. Un vendedor ambulante ofrecía helados en la esquina. Una risa contagiosa resonaba en el aire fresco. <br><br> Los pájaros cantaban melodías alegres en los árboles. La ciudad cobraba vida con la actividad matutina. Una suave lluvia acariciaba la tierra sedienta. El sonido de las olas rompiendo llenaba el aire. Las montañas se perfilaban majestuosamente en el horizonte. Los niños jugaban alegremente en el parque cercano. Una risa contagiosa resonaba en el aire fresco. Los pájaros cantaban melodías alegres en los árboles. Las estrellas brillaban como diamantes en la noche. <br><br> Las estrellas parpadeaban en el cielo nocturno. Las hojas crujían bajo mis pies al caminar. Un gato negro cruzó la calle velozmente. Un piano tocaba una melodía melancólica. El sonido lejano de un violín llegaba a mis oídos. Las estrellas parpadeaban en el cielo nocturno. Las estrellas brillaban como diamantes en la noche. Un anciano alimentaba a las palomas en el parque. El eco de risas resonaba en el viejo teatro. Una sombra se movía en la penumbra de la calle. <br><br> El perfume de las rosas llenaba el jardín secreto. Un gato negro cruzó la calle velozmente. El reloj marcaba las tres de la madrugada. El aroma a café recién hecho llenaba la habitación. Un avión dejó una estela blanca en el cielo azul. Un viejo faro guiaba a los barcos en la oscuridad. El sol brillaba con fuerza sobre el campo de flores. Los fuegos artificiales pintaban el cielo de colores. El sol brillaba con fuerza sobre el campo de flores. Las olas del mar susurraban secretos antiguos. <br><br> </p>
        <h3>Prueba nuestra página en desarrollo <a href='http://secret.ibc'> pinchando aquí.</a> </h3>
    </main>

    <footer id="pie-pagina">
        <p>
			<br><a href='#'>Términos y Condiciones.</a>
			<br><a href='#'>Explora nuestro blog.</a>
			<br><a href='#'>Términos y Condiciones.</a>
			<br><a href='#'>Términos y Condiciones.</a>
		</p>

    </footer>
</body>
</html>
