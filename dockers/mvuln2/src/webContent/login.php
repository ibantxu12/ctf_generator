<?php
session_start();

$host = '127.0.0.1';
$dbname = 'loginweb';
$usuario_bd = 'userweb';
$contrasena_bd = 'userWebExtintor';

try {
    $pdo = new PDO("pgsql:host=$host;dbname=$dbname", $usuario_bd, $contrasena_bd);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    die("Error de conexión a la base de datos: " . $e->getMessage());
}

$usuario = $_POST['user'];
$contrasena = $_POST['password'];
$sql = "SELECT * FROM usuarios WHERE usuario = '$usuario' AND contrasena = '$contrasena'"; /*
$sql = "SELECT * FROM usuarios WHERE usuario = ? AND contrasena = ?";
$stmt = $pdo->prepare($sql);
$stmt->execute([$usuario, $contrasena]);
$usuarioEncontrado = $stmt->fetch(PDO::FETCH_ASSOC);

if ($usuarioEncontrado) {
*/
$result = $pdo->query($sql);
if ($result && $result->fetchColumn() > 0) {
    $_SESSION['usuario'] = $usuario;
    header('Location: inicio.php'); 
    exit();
} else {
    echo "Credenciales incorrectas. Por favor, intenta de nuevo.";
}
?>