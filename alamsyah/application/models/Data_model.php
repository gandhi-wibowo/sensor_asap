<?php

if (!defined('BASEPATH'))
    exit('No direct script access allowed');

class Data_model extends CI_Model{

    function __construct() {
        parent::__construct();
    }
    function insert($value){
      $data = array('data'=>$value);
      $exe = $this->db->insert('data',$data);
      if($exe){
        return TRUE;
      }
      else{
        return FALSE;
      }
    }

}
