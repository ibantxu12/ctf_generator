<?php
session_start();

$host = 'nombre_del_host';
$dbname = 'nombre_de_la_base_de_datos';
$usuario_bd = 'nombre_de_usuario';
$contrasena_bd = 'contrasena_de_usuario';

try {
    $pdo = new PDO("mysql:host=$host;dbname=$dbname", $usuario_bd, $contrasena_bd);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    die("Error de conexión a la base de datos: " . $e->getMessage());
}

$usuario = $_POST['user'];
$contrasena = $_POST['password'];

$sql = "SELECT * FROM usuarios WHERE usuario = ? AND contrasena = ?";
$stmt = $pdo->prepare($sql);
$stmt->execute([$usuario, $contrasena]);
$usuarioEncontrado = $stmt->fetch(PDO::FETCH_ASSOC);

if ($usuarioEncontrado) {

    $_SESSION['usuario'] = $usuario;
    header('Location: inicio.php'); 
} else {
    echo "Credenciales incorrectas. Por favor, intenta de nuevo.";
}
?>
