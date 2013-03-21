<?php
class cX0
{
  private $line = array(
    array(array(0,0),array(0,1),array(0,2)),
    array(array(1,0),array(1,1),array(1,2)),
    array(array(2,0),array(2,1),array(2,2)),
    array(array(0,0),array(1,0),array(2,0)),
    array(array(0,1),array(1,1),array(2,1)),
    array(array(0,2),array(1,2),array(2,2)),
    array(array(0,0),array(1,1),array(2,2)),
    array(array(2,0),array(1,1),array(0,2)));
  private $localLine = array(
    array(array(0,3,6),array(0,4    ),array(0,5,7)),
    array(array(1,3  ),array(1,4,6,7),array(1,5  )),
    array(array(2,3,7),array(2,4    ),array(2,5,6)));

  private $myFigure;   // '0' - Фигура игрока 'Нолики', 'x' - 'Крестики'
  private $firstHod;   // '0' - Первые ходят 'Нолики', 'x' - 'Крестики'
  private $pole;       // -1 - '0', 1 - 'x'

///////////////////////////////////////////////////////////////////////////////
  function __construct($hodHistory, $myFigure = 'x', $firstHod = '0') {
    $this->myFigure = $myFigure == 'x' ? 1 : -1;
    $this->firstHod = $firstHod == 'x' ? 1 : -1;
    if (strlen($hodHistory) == 9)
      for ($y = $i = 0; $y < 3; $y++)
        for ($x = 0; $x < 3; $x++, $i++)
          switch ($hodHistory[$i]) {
            case '0': $this->pole[$y][$x] = -1; break;
            case 'x': $this->pole[$y][$x] = 1;
          }
    $this->SelectHod();
  }
///////////////////////////////////////////////////////////////////////////////
  private function SelectHod() {
    $CountHod = count($this->pole, COUNT_RECURSIVE) - count($this->pole);
    
    $hodAI = ($this->myFigure == $this->firstHod) ? ($CountHod % 2 == 1) : ($CountHod % 2 == 0);

    if ($hodAI and !$this->Stop()) {
      $h = ($CountHod == 0) ? rand(0, 8) : $this->Hod(-$this->myFigure, false);
      $this->pole[$h / 3][$h % 3] = -$this->myFigure;
      $this->Stop();
    }
  }
///////////////////////////////////////////////////////////////////////////////
  private function IzPriz($y, $x) {
    for ($l = 0; isset($this->localLine[$y][$x][$l]); $l++) {
      $lt = $this->localLine[$y][$x][$l];
      for ($n = 0; $n < 3; $n++) {
        $ty = $this->line[$lt][$n][0];
        $tx = $this->line[$lt][$n][1];
        if (!isset($this->pole[$ty][$tx]) or $this->pole[$ty][$tx] != $this->pole[$y][$x])
          break;
      }
      if ($n == 3) return $lt;
    }
    return -1;
  }
///////////////////////////////////////////////////////////////////////////////
  private function Hod($kto, $islocal = true) {
    $CountHod = count($this->pole, COUNT_RECURSIVE) - count($this->pole);
    if ($CountHod >= 9) return;
    
    for ($y = 0; $y < 3; $y++)
      for ($x = 0; $x < 3; $x++)
        if (!isset($this->pole[$y][$x])) {
          $this->pole[$y][$x] = $kto;
          //-------------------------
          if ($this->IzPriz($y, $x) >= 0)
            $attr[$y][$x] = $kto;
          elseif ($CountHod + 1 < 9)
            $attr[$y][$x] = $this->Hod(-$kto);
          else
            $attr[$y][$x] = 0;
          //-------------------------
          unset($this->pole[$y][$x]);
        }

    foreach ($attr as $attr0)
      foreach ($attr0 as $attr00)
        if (isset($extr)) {
          if ($kto == -1) {
            if ($attr00 < $extr)
              $extr = $attr00;
          }
          elseif ($attr00 > $extr)
            $extr = $attr00;
        }
        else
          $extr = $attr00;
    
    if ($islocal) return ($extr);

    for ($y = $i = 0; $y < 3; $y++)
      for ($x = 0; $x < 3; $x++)
        if (isset($attr[$y][$x]) and $attr[$y][$x] == $extr) {
          $attrN[$i] = $y * 3 + $x;
          $i++;
        }
    return $attrN[rand(0, count($attrN) - 1)];
  }
///////////////////////////////////////////////////////////////////////////////
  function PrepareForm($actionPHP) {
    $hodHistory = '';
    for ($y = $i = 0; $y < 3; $y++)
      for ($x = 0; $x < 3; $x++, $i++)
        if (isset($this->pole[$y][$x]))
          if ($this->pole[$y][$x] < 0)
            $hodHistory .= '0';
          elseif ($this->pole[$y][$x] > 0)
            $hodHistory .= 'x';
          else
            $hodHistory .= '?';
        else
          $hodHistory .= '?';
    $myFigure = $this->myFigure == 1 ? 'x' : '0';
    $firstHod = $this->firstHod == 1 ? 'x' : '0';

    $pf = '<form action="' . $actionPHP . '" method="post">';
    $pf .= '<input type="hidden" name="HodHistory" value="' . $hodHistory . '">';
    $pf .= '<input type="hidden" name="MyFigure" value=' . $myFigure . '>';
    $pf .= '<input type="hidden" name="FirstHod" value=' . $firstHod . '>';
    $pf .= '<table border=1>';
    $fCur = $this->myFigure == -1 ? 'Is0' : 'IsX';
    for ($y = 0; $y < 3; $y++) {
      $pf .= '<tr>';
      for ($x = 0; $x < 3; $x++) {
        $pf .= '<td>';
        if (isset($this->pole[$y][$x])) {
          switch ($this->pole[$y][$x]) {
            case -2: $f = 'priz0.gif'; $fn = 'ПризНолик'; break;
            case -1: $f = 'is0.gif'; $fn = 'Нолик'; break;
            case  0: $f = 'isnull.gif'; $fn = 'Пусто'; break;
            case  1: $f = 'isx.gif'; $fn = 'Крестик'; break;
            case  2: $f = 'prizx.gif'; $fn = 'ПризКрестик';
          }
          $pf .= '<img src="picture/' . $f . '" alt="' . $fn . '">';
        }
        else {
          $pf .= '<input type="image" style="cursor : url(picture/' . $fCur . '.cur)" name="pole';
          $pf .= $y . $x . '" src="picture/isnull.gif">';
        }
        $pf .= '</td>';
      }
      $pf .= '</tr>';
    }
    $pf .= '</table>';
    $pf .= '</form>';
    return $pf;
  }
///////////////////////////////////////////////////////////////////////////////
  private function Stop() {
    $CountHod = count($this->pole, COUNT_RECURSIVE) - count($this->pole);
    $fig0 = $fig1 = $fig2 = $fig3 = 0;

    for ($l = 0; $l < 8; $l++) {
      for ($n = $c0 = $cx = 0; $n < 3; $n++) {
        $ty = $this->line[$l][$n][0];
        $tx = $this->line[$l][$n][1];
        if (isset($this->pole[$ty][$tx]))
          if ($this->pole[$ty][$tx] < 0)
            $c0++;
          elseif ($this->pole[$ty][$tx] > 0)
            $cx++;
      }
      if ($cx + $c0 == 0) $fig0++;
      if ($cx + $c0 == 1) $fig1++;
      if (($cx == 0 and $c0 == 2) or ($cx == 2 and $c0 == 0)) $fig2++;
      if ($cx == 3 or $c0 == 3) {
        $fig3++;
        for ($n = 0; $n < 3; $n++) {
          $ty = $this->line[$l][$n][0];
          $tx = $this->line[$l][$n][1];
          $this->pole[$ty][$tx] /= abs($this->pole[$ty][$tx]);
          $this->pole[$ty][$tx] *= 2;
        }
      }
    }

    if ($fig3 > 0)
      $st = true;
    else
      $st = (($fig0 > 1) or ($fig1 > 1) or ($fig2 > 0)) ? false : true;

    if ($st)
      for ($y = 0; $y < 3; $y++)
        for ($x = 0; $x < 3; $x++)
          if (!isset($this->pole[$y][$x]))
            $this->pole[$y][$x] = 0;
    return $st;
  }
///////////////////////////////////////////////////////////////////////////////
}
?>