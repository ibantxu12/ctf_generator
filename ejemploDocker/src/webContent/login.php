<?php
session_start();

$host = '127.0.0.1';
$dbname = 'loginweb';
$usuario_bd = 'userweb';
$contrasena_bd = 'userWebExtintor';

try {
    $pdo = new PDO(##motorbdd##);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    die("Error de conexión a la base de datos: " . $e->getMessage());
}
##sqlinjectionP##
$usuario = $_POST['user'];
$contrasena = $_POST['password'];
$sql = "SELECT * FROM usuarios WHERE usuario = ? AND contrasena = ?";
##sqlinjectionF##

$stmt = $pdo->prepare($sql);
$stmt->execute([$usuario, $contrasena]);
$usuarioEncontrado = $stmt->fetch(PDO::FETCH_ASSOC);

if ($usuarioEncontrado) {

    $_SESSION['usuario'] = $usuario;
    header('Location: inicio.php'); 
    exit();
} else {
    echo "Credenciales incorrectas. Por favor, intenta de nuevo.";
}
?>