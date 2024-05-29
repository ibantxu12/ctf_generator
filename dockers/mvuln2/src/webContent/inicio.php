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
    <link rel='stylesheet' href='styles/inicio4.css'>
</head>
<body>
    <header id="encabezado">
        <h1>Explorando Oportunidades</h1>
 		<img src='img/l5.png' alt='Imagen Aleatoria'>

    </header>

    <nav id="menu">
        <ul>
			<li><a href='#'>Inicio</a></li>
			<li><a href='#'>Ofertas</a></li>
			<li><a href='#'>Blog</a></li>
			<li><a href='#'>Términos y Condiciones</a></li>
			<li><a href='#'>Ofertas</a></li>
		</ul>

    </nav>

    <main id="contenido">
        <p> Gotas de lluvia golpeaban contra la ventana. El viento susurraba secretos entre los árboles. Un aroma delicioso emanaba de la panadería local. Un globo se escapó y flotó hacia el cielo. Una puerta se cerró con un golpe repentino. Las olas del mar susurraban secretos antiguos. Una mariposa revoloteaba cerca de las flores. El aroma a café recién hecho llenaba la habitación. <br><br> Un gato negro cruzó la calle velozmente. Un globo se escapó y flotó hacia el cielo. La ciudad cobraba vida con la actividad matutina. El reloj marcaba el paso implacable del tiempo. Gotas de lluvia golpeaban contra la ventana. El aroma a café recién hecho llenaba la habitación. Las luciérnagas danzaban en la penumbra. Las montañas se perfilaban majestuosamente en el horizonte. <br><br> El reloj marcaba el paso implacable del tiempo. Hojas secas crujían bajo mis pies al caminar. Una puerta se cerró con un golpe repentino. Las montañas se perfilaban majestuosamente en el horizonte. Una suave lluvia acariciaba la tierra sedienta. Las luciérnagas danzaban en la penumbra. Un río tranquilo serpenteaba a través del valle. La Luna iluminaba la noche con su resplandor plateado. El sol brillaba con fuerza sobre el campo de flores. El sonido lejano de un violín llegaba a mis oídos. Una risa contagiosa resonaba en el aire fresco. <br><br> </p>
        <h3>Prueba nuestra página en desarrollo <a href='http://secret.ibc'> pinchando aquí.</a> </h3>
    </main>

    <footer id="pie-pagina">
        <p>
			<br><a href='#'>Descubre nuestra historia.</a>
			<br><a href='#'>Descubre nuestra historia.</a>
			<br><a href='#'>Términos y Condiciones.</a>
			<br><a href='#'>Contáctanos.</a>
			<br><a href='#'>Contáctanos.</a>
		</p>

    </footer>
</body>
</html>
