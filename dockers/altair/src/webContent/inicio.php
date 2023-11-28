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
        <h1>Página Principal</h1>
 		<img src='img/l3.png' alt='Imagen Aleatoria'>

    </header>

    <nav id="menu">
        <ul>
			<li><a href='#'>Inicio</a></li>
			<li><a href='#'>Eventos</a></li>
			<li><a href='#'>Galería</a></li>
			<li><a href='#'>Blog</a></li>
			<li><a href='#'>FAQ (Preguntas Frecuentes)</a></li>
			<li><a href='#'>Productos</a></li>
		</ul>

    </nav>

    <main id="contenido">
        <p> Los fuegos artificiales pintaban el cielo de colores. Una sombra se movía en la penumbra de la calle. Las luciérnagas danzaban en la penumbra. Una sombra misteriosa se deslizaba por el callejón. La ciudad cobraba vida con la actividad matutina. Un globo se escapó y flotó hacia el cielo. El tren rugía mientras se alejaba en la distancia. Un globo se escapó y flotó hacia el cielo. El viento susurraba secretos entre los árboles. <br><br> El sonido lejano de un violín llegaba a mis oídos. Una suave brisa acariciaba la superficie del agua. Una risa contagiosa resonaba en el aire fresco. Una sombra se movía en la penumbra de la calle. El aroma a café recién hecho llenaba la habitación. Una risa estruendosa resonó en el silencio. La ciudad cobraba vida con la actividad matutina. Hojas secas crujían bajo mis pies al caminar. El tren rugía mientras se alejaba en la distancia. <br><br> El aroma a café recién hecho llenaba la habitación. Un vendedor ambulante ofrecía helados en la esquina. Luces parpadeantes adornaban la calle principal. Las hojas crujían bajo mis pies al caminar. Un arco iris adornaba el cielo después de la lluvia. Una risa contagiosa resonaba en el aire fresco. Una suave lluvia acariciaba la tierra sedienta. Una risa contagiosa resonaba en el aire fresco. <br><br> </p>
    </main>

    <footer id="pie-pagina">
        <p>
			<br><a href='#'>Descubre nuestra historia.</a>
			<br><a href='#'>Únete a nuestra comunidad.</a>
			<br><a href='#'>Acerca de Nosotros.</a>
			<br><a href='#'>Únete a nuestra comunidad.</a>
		</p>

    </footer>
</body>
</html>
