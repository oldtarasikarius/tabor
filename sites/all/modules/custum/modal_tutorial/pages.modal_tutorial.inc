<?php
/**
 * @file
 * Contains all page callbacks.
 */

/**
 * Page callback
 */
function modal_tutorial_page_callback() {
  ctools_include('ajax');
  ctools_include('modal');
  ctools_modal_add_js();
  $build['paragraph'] = array(
    '#prefix' => '<p>',
    '#suffix' => '</p>',
    '#markup' => t('Click on the button to show a cool modal'),
  );
  
  $text = t('Show a popup');
  $dest = 'ajax/nojs/show/modal';
  $alt = t('Show a popup by a clicking');
  $link = ctools_modal_text_button($text, $dest, $alt);
  
  $build['popup_link'] = array(
    '#markup' => $link,
  );
 
  return render($build);
}

/**
 * Modal window build.
 */
function ajax_modal_tutorial_page_callback($js = NULL) {
  ctools_include('ajax');
  ctools_include('modal');
  if ($js) {
    $title = t('Custom modal window');
    $build = array(
      '#prefix' => '<p>',
      '#suffix' => '</p>',
      '#markup' => t('Content of test custom modal window'),
    );
    $output = render($build);
    ctools_modal_render($title, $output);
  }
}
