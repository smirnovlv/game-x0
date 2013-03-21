<html>

<?php
  $f = fopen('stat.dat', 'a+');
  flock($f, LOCK_EX);
  $count = fread($f, 100);
  @$count++;
  ftruncate($f, 0);
  fwrite($f, $count);
  fflush($f);
  flock($f, LOCK_UN);
  fclose($f);
/*  $text = "'A[[B[C][D]E[F[J]]H][K]L]M";
  $html = preg_replace(
  '/
    \[
      (              # Начало нужного кармана
        [^\[]*?
      )              # Конец нужного кармана
    \]
  /isx', '($1)', $text);
  echo $html;
*/  
/*
  $f = fopen('stat.dat', 'a+');
  flock($f, LOCK_EX);
  $count = fread($f,100);
  flock($f, LOCK_UN);
  fclose($f);
  echo "Количество скачек/кликов: $count";
*/  
  require_once('include/header.inc');
?>

<frameset rows="20%,80%">  
  <frame src="menu.php" noresize>
  <frame src="work.php" name="work">
</frameset>
</html>