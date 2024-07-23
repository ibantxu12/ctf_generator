<?php
    if (isset($_GET['page'])) {
        $page = $_GET['page'];
        include($page);
    } else {
        echo "No page specified.";
    }
?>
