<?php

if (!defined('BASEPATH'))
    exit('No direct script access allowed');

class Saklar_model extends CI_Model{

    function __construct() {
        parent::__construct();
    }
    function get_by_id($id){ // dapatkan data berdasarkan id
      $query = "SELECT * FROM saklar WHERE id_saklar = '$id'";
      return $this->db->query($query)->result();
    }
    function update($id,$status){
      $query = "UPDATE  `saklar` SET  `status` =  '$status' WHERE  `id_saklar` ='$id'";

    }

}
