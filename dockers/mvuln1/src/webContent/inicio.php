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
        <h1>Explorando Oportunidades</h1>
 		<img src='img/l6.png' alt='Imagen Aleatoria'>

    </header>

    <nav id="menu">
        <ul>
			<li><a href='#'>Inicio</a></li>
			<li><a href='#'>Eventos</a></li>
			<li><a href='#'>Ofertas</a></li>
			<li><a href='#'>FAQ (Preguntas Frecuentes)</a></li>
			<li><a href='#'>Eventos</a></li>
		</ul>

    </nav>

    <main id="contenido">
        <p> Las olas del mar susurraban secretos antiguos. Las luciérnagas danzaban en la penumbra. El reloj marcaba las tres de la madrugada. Una sombra se movía en la penumbra de la calle. El sonido lejano de un violín llegaba a mis oídos. El aroma a café llenaba la pequeña cafetería. Un anciano contaba historias en el banco del parque. Risas de niños resonaban en el parque infantil. El eco de risas resonaba en el viejo teatro. La ciudad cobraba vida con la actividad matutina. Una sombra se movía en la penumbra de la calle. <br><br> Una sombra se movía en la penumbra de la calle. Las olas del mar susurraban secretos antiguos. Los niños jugaban alegremente en el parque cercano. Un río tranquilo serpenteaba a través del valle. Un avión dejó una estela blanca en el cielo azul. Las estrellas brillaban como diamantes en la noche. El eco de risas resonaba en el viejo teatro. El sonido lejano de un violín llegaba a mis oídos. <br><br> Una sombra se movía en la penumbra de la calle. Risas de niños resonaban en el parque infantil. Un vendedor ambulante ofrecía helados en la esquina. Las estrellas parpadeaban en el cielo nocturno. Las luciérnagas danzaban en la penumbra. Una puerta se cerró con un golpe repentino. La ciudad cobraba vida con la actividad matutina. El aroma a café recién hecho llenaba la habitación. El eco de risas resonaba en el viejo teatro. <br><br> Un vendedor ambulante ofrecía helados en la esquina. El perfume de las rosas llenaba el jardín secreto. El reloj marcaba el paso implacable del tiempo. Un arco iris adornaba el cielo después de la lluvia. Murmullos de conversación llenaban el café. <br><br> Murmullos de conversación llenaban el café. Un viejo faro guiaba a los barcos en la oscuridad. Las luciérnagas danzaban en la penumbra. Las luciérnagas danzaban en la penumbra. Un anciano alimentaba a las palomas en el parque. Una bicicleta oxidada descansaba junto al poste. Un avión dejó una estela blanca en el cielo azul. <br><br> Las estrellas brillaban como diamantes en la noche. Murmullos de conversación llenaban el café. Los niños jugaban alegremente en el parque cercano. El aroma a café recién hecho llenaba la habitación. El sonido lejano de un violín llegaba a mis oídos. <br><br> El graznido de un cuervo rompió el silencio. El aroma a café recién hecho llenaba la habitación. Un avión dejó una estela blanca en el cielo azul. Un río tranquilo serpenteaba a través del valle. Las hojas crujían bajo mis pies al caminar. <br><br> </p>
        <h3>Prueba nuestra página en desarrollo <a href='http://secret.ibc'> pinchando aquí.</a> </h3>
    </main>

    <footer id="pie-pagina">
        <p>
			<br><a href='#'>Acerca de Nosotros.</a>
			<br><a href='#'>Últimas actualizaciones aquí.</a>
			<br><a href='#'>Tu privacidad es importante.</a>
			<br><a href='#'>Tu privacidad es importante.</a>
		</p>

    </footer>
</body>
</html>
