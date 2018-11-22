pipeline {
  agent {
    dockerfile {
      filename 'Dockerfile'
    }

  }
  stages {
    stage('pyhton version') {
      steps {
        sh 'python --version'
        sh 'scons --version'
      }
    }
    stage('build UnitTest') {
      steps {
        sh 'scons UnitTest'
      }
    }
    stage('Test') {
      steps {
        sh 'cd build/UnitTest_release && ./UnitTest --gtest_output=xml:unit_test_results.xml'
      }
    }
  }
}